/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2012-2015, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the COPYING file in this distribution for license details.
 * ----------------------------------------------------------------------
 */

#ifndef VRT_QUEUE_H
#define VRT_QUEUE_H
typedef int  vrt_value_id;

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "atomic.h"

#include "yield.h"
#ifdef __cplusplus
extern "C" {
#endif


/** A FIFO queue modeled after the Java Disruptor project. */
struct vrt_queue {

    /** One less than the size of this queue.  The actual value count
     * will always be a power of 2, so this value will always be an
     * AND-mask that lets you easily calculate (x % value_count). */
    unsigned int  value_mask;
    // data type's size
    unsigned int type_size;
    /** The consumers feeding this queue. */
    struct vrt_padded_int consumer_cursor[10];
    unsigned int real_consumer_num;
    
    unsigned int real_producer_num;
    /** The last item that we know every consumer has finished
     * processing. */
    vrt_value_id  last_consumed_id;

    /** The last item that has been claimed by a producer.  This will
     * only be updated if we have multiple producers; if there's only
     * one, it doesn't need to coordinate with anyone, and keeps track
     * of its last claimed value internally. */
    struct vrt_padded_int  last_claimed_id;

    /** The next value ID that can be written into the queue. */
    struct vrt_padded_int  cursor;

    /** A name for the queue */
    char  name[50];
};

/** Allocate a new queue. */
struct vrt_queue *
vrt_queue_new(const char *name, 
              unsigned int value_count,unsigned int type_size, int *shm_fd);

struct vrt_queue *
vrt_queue_acquire(const char *name, int *shm_fd);

/** Free a queue. */
void
vrt_queue_free(struct vrt_queue *q, int shm_fd, bool un_link);



/* Compare two integers on the modular-arithmetic ring that fits into an int. */
#define vrt_mod_lt(a, b) (0 < ((b)-(a)))
#define vrt_mod_le(a, b) (0 <= ((b)-(a)))

/** Return the number of values managed by the queue. */
#define vrt_queue_size(q) \
    ((q)->value_mask + 1)

/** Retrieve the value with the given ID. */
#define vrt_queue_get(q, id) \
    ((id) & (q)->value_mask)

/** Return the ID of the value that was most recently published into the
 * queue.  This function involves a memory barrier, and so it should be
 * called sparingly. */

static inline vrt_value_id
vrt_queue_get_cursor(struct vrt_queue *q)
{
    return vrt_padded_int_get(&q->cursor);
}

/** Set the ID of the value that was most recently published into the
 * queue.  This function involves a memory barrier, and so it should be
 * called sparingly.  Moreover, it's an interal method; client code
 * shouldn't need to call this directly. */

static inline void
vrt_queue_set_cursor(struct vrt_queue *q, vrt_value_id value)
{
    vrt_padded_int_set(&q->cursor, value);
}


/*-----------------------------------------------------------------------
 * Producers
 */

/**
 * A producer is an object that feeds values into a queue.  The queue
 * manages the storage of the objects, however, so a producer works by
 * "claiming" the next free object in the queue.  It then fills in the
 * object as needed, and finally "publishes" the filled-in object, which
 * makes it available to the queue's consumers.  The object is
 * considered live until all consumers inform the queue that they're
 * done with the object.  At that point, the value's slot in the queue's
 * array can be reused by another object.
 */
struct vrt_producer {
    /** The queue that this producer feeds */
    struct vrt_queue  *queue;

    /** The index of this producer within its queue */
    unsigned int  index;

    /** The ID of the last value that was returned by the producer. */
    vrt_value_id  last_produced_id;

    /**
     * The ID of the last value that's currently claimed by the
     * producer.  This field is undefined if the producer hasn't claimed
     * a value yet.
     */
    vrt_value_id  last_claimed_id;

    /**
     * The function that the producer will use to claim a value ID from
     * the queue.  This is filled in by the vrt_queue_add_producer
     * function.  The particular function used depends on how many
     * producers are connected to the queue.  (If there's only one, we
     * can use a faster implementation.)
     *
     * This function won't return until there's a value to give to the
     * producer.  If the queue is currently full, this function will
     * call the producer's yield method to allow other producers and
     * consumers to run.
     */
    int
    (*claim)(struct vrt_queue *q, struct vrt_producer *self);

    /**
     * The function that the producer will use to publish a value ID to
     * the queue.  This is filled in by the vrt_queue_add_producer
     * function.  The particular function used depends on how many
     * producers are connected to the queue.  (If there's only one, we
     * can use a faster implementation.)
     */
    int
    (*publish)(struct vrt_queue *q, struct vrt_producer *self,
               vrt_value_id last_published_id);

    /** The number of values to claim at once. */
    unsigned int  batch_size;

    /** The yield strategy to use when the producer operations would
     * block. */
    struct vrt_yield_strategy  *yield;

    /** A name for the producer */
    char  name[50];

};

/** Allocate a new producer that will feed the given queue.  The
 * producer will claim batch_size values at a time.  If batch_size is 0,
 * then we'll calculate a reasonable default batch size. */
struct vrt_producer *
vrt_producer_new(const char *name, unsigned int batch_size,
                 struct vrt_queue *q, unsigned int  starting_idx, bool is_single_producer);

/** Free a producer */
void
vrt_producer_free(struct vrt_producer *p);

/** Claim the next value managed by the producer's queue.  If this
 * returns without an error, a value instance will be loaded into @ref
 * value.  The caller has full control over the contents of this value. */
int
vrt_producer_claim(struct vrt_producer *p, int *posi);

/** Publish the most recently claimed value.  This function won't return
 * until the value is successfully published to the queue's consumers.
 * Once this function returns, the caller no longer has any rights to
 * the claimed value.  (Even for reading!)  The queue is allowed to
 * overwrite its contents at will. */
int
vrt_producer_publish(struct vrt_producer *p);
int
vrt_producer_flush(struct vrt_producer *p);



/*-----------------------------------------------------------------------
 * Consumers
 */

/**
 * A consumer is an object that drains values from a queue.  The
 * consumer must check the queue's cursor to see determine the ID of the
 * most recently published value.  The consumer also maintains the ID of
 * the last value that it extracted.  This allows the consumer to know
 * which entries in the queue are safe to be read.
 *
 * The producers of the queue peek at each consumer's cursor to
 * determine when it's safe to write to the queue.  (This is how we
 * protect against wrapping around within the queue's ring buffer.)
 * This means that access to the consumer's cursor must be thread-safe.
 * You must *never* access the cursor field directly; you must *always*
 * use the vrt_consumer_get_cursor and vrt_consumer_set_cursor
 * functions.
 *
 * One simplifying assumption that we have to make is that when the
 * consumer's client calls next_entry, it has completely finished with
 * all previous values.  You cannot save the value pointer to be used
 * later on, since it will almost certainly be overwritten later on by a
 * different value.  The consumer's client is responsible for extracting
 * any needed contents and stashing them into some other bit of storage
 * before retrieving the next value.
 */
struct vrt_consumer {
    /** The queue that this consumer feeds */
    struct vrt_queue  *queue;

    /** The index of this consumer within its queue */
    unsigned int  index;



    /** The last value that we know is available for processing.  This
     * field is not thread-safe, and allows us to process a chunk of
     * values without yielding. */
    vrt_value_id  last_available_id;

    /** The value that's currently being consumed. */
    vrt_value_id  current_id;

    /** The yield strategy to use when the consumer operations would
     * block. */
    struct vrt_yield_strategy  *yield;

    /** A name for the consumer */
    char  name[50];
};

/** Allocate a new consumer that will drain the given queue. */
struct vrt_consumer *
vrt_consumer_new(const char *name, struct vrt_queue *q, unsigned int  starting_idx);

/** Free a consumer */
void
vrt_consumer_free(struct vrt_consumer *c);



/** Retrieve the next value from the consumer's queue.  If this function
 * returns successfully, then @ref value will be filled in with the next
 * value in the queue.  The caller then has full read access to the
 * contents of that value.  The value instance will only be valid until
 * the next call to @c vrt_consumer_next.  At that point, the queue
 * is free to overwrite the contents of the value at will. */
int
vrt_consumer_next(struct vrt_consumer *c, int *posi);
int vrt_consumer_next_no_waiting(struct vrt_consumer *c, int *posi);

/* 判断当前消费者是否还有可消费的数据
 * 返回 1 代表空，无数据可供消费
 * 返回 0 代表 有数据
 */
int vrt_consumer_is_empty(struct vrt_consumer *c , int *size);
int vrt_consumer_next_no_check(struct vrt_consumer *c, int *posi);

/** Return the ID of the value that was most recently processed by this
 * consumer.  This function involves a memory barrier, and so it should
 * be called sparingly. */

static inline vrt_value_id
vrt_consumer_get_cursor(struct vrt_padded_int padded)
{
    return vrt_padded_int_get(&padded);
}

/** Set the ID of the value that was most recently processed by this
 * consumer.  This function involves a memory barrier, and so it should
 * be called sparingly.  Moreover, it's an interal method; client code
 * shouldn't need to call this directly. */

static inline void
vrt_consumer_set_cursor(struct vrt_queue *q,struct vrt_consumer *c, vrt_value_id value)
{
    vrt_padded_int_set(&(q->consumer_cursor[c->index]), value);
}


static inline void* createSHM(const char *name,long int len ,int *shm_fd) {
    void *t;
    *shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (*shm_fd == -1) {
      printf("createSHM: Shared memory %s failed: %s\n", name, strerror(errno));
      exit(1);
      //return malloc(len);
    }
    ftruncate(*shm_fd, len);
    t = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, *shm_fd, 0);
    if (t == MAP_FAILED) {
      printf("createSHM: Map %s failed: %s\n", name, strerror(errno));
      exit(1);
      //return malloc(len);
    }
    return t;
}

static inline void* getSHM(const char *name,long int len, bool rdonly,int *shm_fd) {
    void *t;
    int oflag = O_RDONLY;//file open flag
    int prot = PROT_READ;//memory page prorection flag
    if (!rdonly) {
        oflag = O_RDWR;
        prot = PROT_READ | PROT_WRITE;
    }
    *shm_fd = shm_open(name, oflag, 0666);    
    if (*shm_fd == -1) {
      printf("getSHM: Shared memory %s failed: %s\n", name, strerror(errno));
      exit(1);
      //return malloc(len);
    }
    ftruncate(*shm_fd, len);
    t = mmap(0, len, prot, MAP_SHARED, *shm_fd, 0);
    if (t == MAP_FAILED) {
      printf("getSHM: Map %s failed: %s\n", name, strerror(errno));
      exit(1);
      //return malloc(len);
    }
    return t;
}


static inline void* vrt_data_new(const char *name, long int len, int *shm_fd) {
   return createSHM(name, len, shm_fd);
}
static inline void* vrt_data_acquire(const char *name, long int len, int *shm_fd, bool rdonly) {
    return getSHM(name, len, rdonly, shm_fd);;
}
void vrt_data_free(void *pdata,const char * name, long int len, int shm_fd, bool un_link) ;
#ifdef __cplusplus
}
#endif

#endif /* VRT_QUEUE_H */
