/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2012-2015, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the COPYING file in this distribution for license details.
 * ----------------------------------------------------------------------
 */
#define _BSD_SOURCE
#include <assert.h>

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "header/clogger.h"
#include "header/atomic.h"
#include "header/queue.h"
#include "header/yield.h"

#define CLOG_CHANNEL  "vrt"


#define MINIMUM_QUEUE_SIZE  16
#define DEFAULT_QUEUE_SIZE  65536
#define DEFAULT_BATCH_SIZE  4096


/*-----------------------------------------------------------------------
 * Tests
 */

static unsigned int  starting_value = 0;






/*-----------------------------------------------------------------------
 * Queues
 */

/** Returns the smallest power of 2 that is >= in. */
static inline unsigned int
min_power_of_2(unsigned int in)
{
    unsigned int  v = in;
    unsigned int  r = 1;
    while (v >>= 1) {
        r <<= 1;
    }
    if (r != in) {
        r <<= 1;
    }
    return r;
}

struct vrt_queue *
vrt_queue_acquire(const char *name,int *shm_fd) { 
    return (struct vrt_queue*)getSHM(name, sizeof(struct vrt_queue), false, shm_fd);
}

struct vrt_queue *
vrt_queue_new(const char *name,unsigned int size ,unsigned int type_size ,int *shm_fd)
{
    struct vrt_queue  *q = (struct  vrt_queue*)createSHM(name,sizeof(struct vrt_queue) ,shm_fd);
    memset(q, 0, sizeof(struct vrt_queue));
    unsigned int  value_count = 0;
    if (size == 0) {
        value_count = DEFAULT_QUEUE_SIZE;
    } else {
        if (size < MINIMUM_QUEUE_SIZE) {
            size = MINIMUM_QUEUE_SIZE;
        }
        value_count = min_power_of_2(size);
    }
    strcpy(q->name,name);
    q->type_size = type_size;
    q->value_mask = value_count - 1;
    q->last_consumed_id = starting_value;
    q->last_claimed_id.value = q->last_consumed_id;
    q->cursor.value = q->last_consumed_id;
    clog_debug("[%s] Create queue with %u entries", q->name, value_count);
    return q;
}


void vrt_data_free(void *pdata,const char * name, long int len, int shm_fd, bool un_link) {
    if (munmap(pdata, len) == -1) {
      printf("cons: Unmap failed: %s\n", strerror(errno));
      exit(1);
    }
    /* close the shared memory segment as if it was a file */
    if (close(shm_fd) == -1) {
      printf("cons: Close failed: %s\n", strerror(errno));
      exit(1);
    }
    if (un_link) {
      /* remove the shared memory segment from the file system */
      if (shm_unlink(name) == -1) {
        printf("cons: Error removing %s: %s\n", name, strerror(errno));
        exit(1);
      }
    }
}

void
vrt_queue_free(struct vrt_queue *q,int shm_fd, bool un_link)
{
  char name[50];
  strcpy(name,q->name);
  vrt_data_free(q, name, sizeof(struct vrt_queue), shm_fd, un_link);
}



static vrt_value_id
vrt_minimum_cursor(struct vrt_queue *q)
{
    if(q->real_consumer_num = 0) { //当前还没有attach 消费者
        return 0;
    }
    /* We know there's always at least one consumer */
    unsigned int  i;
    vrt_value_id  minimum =
        vrt_consumer_get_cursor(q->consumer_cursor[0]);
    for (i = 1; i < q->real_consumer_num; i++) {
        vrt_value_id  id =
            vrt_consumer_get_cursor(q->consumer_cursor[i]);
        if (vrt_mod_lt(id, minimum)) {
            minimum = id;
        }
    }
    return minimum;
}

#define vrt_queue_find_last_consumed_id(q) \
    vrt_minimum_cursor(q)

/* Waits for the slot given by the producer's last_claimed_id to become
 * free.  (This happens when every consumer has finished processing the
 * previous value that would've used the same slot in the ring buffer. */
static int
vrt_wait_for_slot(struct vrt_queue *q, struct vrt_producer *p)
{
    // Don't need to wait for the value to consumed, if the queue is full, overwrite the value.
    /*
    bool  first = true;
    vrt_value_id  wrapped_id = p->last_claimed_id - vrt_queue_size(q);
    if (vrt_mod_lt(q->last_consumed_id, wrapped_id)) {
        clog_debug("<%s> Wait for value %d to be consumed",
                   p->name, wrapped_id);
        vrt_value_id  minimum = vrt_queue_find_last_consumed_id(q);
        while (vrt_mod_lt(minimum, wrapped_id)) {
            clog_trace("<%s> Last consumed value is %d (wait)",
                       p->name, minimum);
            vrt_yield_strategy_yield(p->yield, first, q->name, p->name);
            first = false;
            minimum = vrt_queue_find_last_consumed_id(q);
        }
        q->last_consumed_id = minimum;
        clog_debug("<%s> Last consumed value is %d", p->name, minimum);
    }
    */
    return 0;
}


static int
vrt_claim_single_threaded(struct vrt_queue *q, struct vrt_producer *p)
{
    /* If there's only a single producer, we can just grab the next
     * batch of values in sequence. */
    p->last_claimed_id += p->batch_size;
    if (p->batch_size == 1) {
        clog_trace("<%s> Claim value %d (single-threaded)",
                   p->name, p->last_claimed_id);
    } else {
        clog_trace("<%s> Claim values %d-%d (single-threaded)",
                   p->name, p->last_claimed_id - p->batch_size + 1,
                   p->last_claimed_id);
    }

    /* But we do have to wait until the slots for these new values are
     * free. */
    return vrt_wait_for_slot(q, p);
}

static int
vrt_claim_multi_threaded(struct vrt_queue *q, struct vrt_producer *p)
{
    /* If there are multiple producerwe have to use an atomic
     * increment to claim the next batch of records. */
    p->last_claimed_id =
        vrt_padded_int_atomic_add(&q->last_claimed_id, p->batch_size);
    p->last_produced_id = p->last_claimed_id - p->batch_size;
    if (p->batch_size == 1) {
        clog_trace("<%s> Claim value %d (multi-threaded)",
                   p->name, p->last_claimed_id);
    } else {
        clog_trace("<%s> Claim values %d-%d (multi-threaded)",
                   p->name, p->last_produced_id + 1, p->last_claimed_id);
    }

    /* Then wait until the slots for these new values are free. */
    return vrt_wait_for_slot(q, p);
}

static int
vrt_publish_single_threaded(struct vrt_queue *q, struct vrt_producer *p,
                            vrt_value_id last_published_id)
{
    /* If there's only a single producer, we can just update the queue's
     * cursor.  We don't have to wait for anything, because the claim
     * function will have already ensured that this slot was free to
     * fill in and publish. */
    clog_debug("<%s> Signal publication of value %d (single-threaded)",
               p->name, last_published_id);
    vrt_queue_set_cursor(q, last_published_id);
    return 0;
}

static int
vrt_publish_multi_threaded(struct vrt_queue *q, struct vrt_producer *p,
                           vrt_value_id last_published_id)
{
    bool  first = true;
    vrt_value_id  expected_cursor;
    vrt_value_id  current_cursor;

    /* If there are multiple publisherthen we have to wait until all
     * of the values before the chunk that we claimed have been
     * published.  (If we don't, there will be a hole in the sequence of
     * published records.) */
    expected_cursor = last_published_id - p->batch_size;
    current_cursor = vrt_queue_get_cursor(q);
    clog_debug("<%s> Wait for value %d to be published",
               p->name, expected_cursor);

    while (vrt_mod_lt(current_cursor, expected_cursor)) {
        clog_trace("<%s> Last published value is %d (wait)",
                   p->name, current_cursor);
        vrt_yield_strategy_yield(p->yield, first, q->name, p->name);
        first = false;
        current_cursor = vrt_queue_get_cursor(q);
    }

    clog_debug("<%s> Last published value is %d", p->name, current_cursor);
    clog_debug("<%s> Signal publication of value %d (multi-threaded)",
               p->name, last_published_id);
    vrt_queue_set_cursor(q, last_published_id);
    return 0;
}

//调用处维护index，第一个producer的index为0，依次增加
static int
vrt_queue_add_producer(struct vrt_queue *q, struct vrt_producer *p,bool is_single_producer)
{
    clog_debug("[%s] Add producer %s", q->name, p->name);
    q->real_producer_num += 1;
    p->queue = q;
    p->index = q->real_producer_num - 1;
    /* Choose the right claim and publish implementations for this
     * producer. */
    if (is_single_producer) {
        /* If this is the first producer, use faster claim and publish
         * methods that are optimized for the single-producer case. */
        p->claim = vrt_claim_single_threaded;
        p->publish = vrt_publish_single_threaded;
    } else {
        /* Otherwise we need to use slower, but multiple-producer-
         * capable, implementations of claim and publish. */
        p->claim = vrt_claim_multi_threaded;
        p->publish = vrt_publish_multi_threaded;
    }

    return 0;
}

static int
vrt_queue_add_consumer(struct vrt_queue *q, struct vrt_consumer *c)
{
    clog_debug("[%s] Add consumer %s", q->name, c->name);
    q->real_consumer_num += 1;
    c->queue = q;
    c->index = q->real_consumer_num - 1;
    return 0;
}


/*-----------------------------------------------------------------------
 * Producers
 */

struct vrt_producer *
vrt_producer_new(const char *name, unsigned int batch_size,
                 struct vrt_queue *q ,unsigned int  starting_idx,bool is_single_producer)
{
    struct vrt_producer  *p;
    unsigned int  maximum_batch_size;

    p = malloc(sizeof(struct vrt_producer));
    memset(p, 0, sizeof(struct vrt_producer));

    strcpy(p->name,name);
    vrt_queue_add_producer(q, p,is_single_producer);

    if (batch_size == 0) {
        batch_size = DEFAULT_BATCH_SIZE;
    }
    maximum_batch_size = vrt_queue_size(q) / 4;
    if (batch_size > maximum_batch_size) {
        batch_size = maximum_batch_size;
    }
    clog_trace("<%s> Batch size is %u", name, batch_size);

    p->last_produced_id = starting_idx;
    p->last_claimed_id = starting_idx;
    p->batch_size = batch_size;
    p->yield = NULL;

    return p;
}

void
vrt_producer_free(struct vrt_producer *p)
{
    free(p);
}

/* Claims the next ID that this producer can fill in.  The new value's
 * ID will be stored in p->last_produced_id.  You can get the value
 * itself using vrt_queue_get. */
static int
vrt_producer_claim_raw(struct vrt_queue *q, struct vrt_producer *p)
{
    if (p->last_produced_id == p->last_claimed_id) {
        p->claim(q, p);
    }
    p->last_produced_id++;
    clog_trace("<%s> Claimed value %d (%d is available)\n",
               p->name, p->last_produced_id, p->last_claimed_id);
    return 0;
}

int
vrt_producer_claim(struct vrt_producer *p, int *posi)
{
    vrt_producer_claim_raw(p->queue, p);
    *posi = vrt_queue_get(p->queue, p->last_produced_id);
    return 0;
}

int
vrt_producer_publish(struct vrt_producer *p)
{   
    if (p->last_produced_id == p->last_claimed_id) {
        return p->publish(p->queue, p, p->last_claimed_id);
    } else {
        clog_trace("<%s> Wait to publish %d until end of batch (at %d)",
                   p->name, p->last_produced_id, p->last_claimed_id);
        return 0;
    }
}

// 刷新未发布到队列的数据，如果还有未填充的claimed id。
int
vrt_producer_flush(struct vrt_producer *p)
{
    if (p->last_produced_id == p->last_claimed_id) {
        /* We don't have any queue entries that we've claimed but haven't used,
         * so there's nothing to flush. */
        return 0;
    }


    /* If we've claimed more value than we've produced, fill in the
     * remainder with holes. */
    if (vrt_mod_lt(p->last_produced_id, p->last_claimed_id)) {
        p->last_claimed_id = p->last_produced_id;
    }

    return p->publish(p->queue, p, p->last_claimed_id);
}


/*-----------------------------------------------------------------------
 * Consumers
 */

struct vrt_consumer *
vrt_consumer_new(const char *name, struct vrt_queue *q, unsigned int  starting_idx)
{
    struct vrt_consumer  *c = malloc(sizeof(struct vrt_consumer));;
    memset(c, 0, sizeof(struct vrt_consumer));
    strcpy(c->name,name);
   

    vrt_queue_add_consumer(q, c);
    q->consumer_cursor[c->index].value = starting_idx;
    c->last_available_id = starting_idx;
    c->current_id = starting_idx;
    return c;
}

void
vrt_consumer_free(struct vrt_consumer *c)
{
    free(c);
}



/* Retrieves the next value from the consumer's queue.  When this
 * returns c->current_id will be the ID of the next value.  You can
 * retrieve the value using vrt_queue_get. */
static int
vrt_consumer_next_raw(struct vrt_queue *q, struct vrt_consumer *c)
{
    /* We've just finished processing the current_id'th value. */
    vrt_value_id  last_consumed_id = c->current_id++;

    /* If we know there are values available that we haven't yet
     * consumed, go ahead and return one. */
    if (vrt_mod_le(c->current_id, c->last_available_id)) {
        clog_trace("<%s> Next value is %d (already available)",
                   c->name, c->current_id);
        return 0;
    }

    /* We've run out of values that we know can been processed.  Notify
     * the world how much we've processed so far. */
    /*队列为空*/
    clog_debug("<%s> Signal consumption of %d", c->name, last_consumed_id);
    //修改消费者当前消费到的位置，如果发布者不需要等待消费者，不管是否被消费直接覆盖数据；则无需修改consumer_cursor。
    //vrt_consumer_set_cursor(q,c, last_consumed_id);

    /* Check to see if there are any more values that we can process. */
    bool  first = true;
    vrt_value_id  last_available_id;
    clog_debug("<%s> Wait for value %d", c->name, c->current_id);

    /* If we don't have any dependencies check the queue itself to see how
     * many values have been published. */
    last_available_id = vrt_queue_get_cursor(q);
    while (vrt_mod_le(last_available_id, last_consumed_id)) {
        clog_trace("<%s> Last available value is %d (wait)",
                   c->name, last_available_id);
        vrt_yield_strategy_yield(c->yield, first, q->name, c->name);
        first = false;
        last_available_id = vrt_queue_get_cursor(q);
    }
    c->last_available_id = last_available_id;
    clog_debug("<%s> Last available value is %d",
               c->name, last_available_id);

    /* Once we fall through to here, we know that there are additional
     * values that we can process. */
    clog_trace("<%s> Next value is %d", c->name, c->current_id);
    return 0;
}

int
vrt_consumer_next(struct vrt_consumer *c, int *posi)
{
    vrt_consumer_next_raw(c->queue, c);
    *posi = vrt_queue_get(c->queue, c->current_id);
    return 0;
}

/*消费队列中的数据，如果队列为空，不需要等待，直接返回告知队列为空。
 * 返回 1 代表队列为空
 * 返回 0 代表队列不为空
 */
int vrt_consumer_next_no_waiting(struct vrt_consumer *c, int *posi) {
    vrt_value_id  last_consumed_id = c->current_id++;
    if (vrt_mod_le(c->current_id, c->last_available_id)) {
        clog_trace("<%s> Next value is %d (already available)",
                   c->name, c->current_id);
        *posi = vrt_queue_get(c->queue, c->current_id);
        return 0;
    }

    vrt_value_id  last_available_id = vrt_queue_get_cursor(c->queue);
    if (vrt_mod_le(last_available_id, last_consumed_id)) { //队列为空,无可消费的槽位
        c->current_id--;
        return 1;
    }
    c->last_available_id = last_available_id;
    *posi = vrt_queue_get(c->queue, c->current_id);
    return 0;
}

/* 判断当前消费者是否还有可消费的数据
 * 返回 1 代表空，无数据可供消费
 * 返回 0 代表 有数据
 */
int vrt_consumer_is_empty(struct vrt_consumer *c , int *size) {
    if (vrt_mod_lt(c->current_id, c->last_available_id)) {
        *size = c->last_available_id - c->current_id;
        return 0;
    }
    vrt_value_id  last_available_id = vrt_queue_get_cursor(c->queue);
    if (vrt_mod_le(last_available_id, c->current_id)) {
        *size = 0;
        return 1;
    } else {
        c->last_available_id = last_available_id;
        *size = c->last_available_id - c->current_id;
        return 0;
    }
}

//vrt_consumer_is_empty 负责检查是否有数据可供消费
int vrt_consumer_next_no_check(struct vrt_consumer *c, int *posi) {
    c->current_id++;
    *posi = vrt_queue_get(c->queue, c->current_id);
    return 0;
}