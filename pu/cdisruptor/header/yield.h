/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2012, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the COPYING file in this distribution for license
 * details.
 * ----------------------------------------------------------------------
 */

#ifndef VRT_YIELD_H
#define VRT_YIELD_H
#include <unistd.h>
#include <limits.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------
 * Yielding strategies
 */

/* Each producer and consumer will yield to other queue clients when one
 * of their operations wouldn't succeed immediately.  Right now, we
 * support a number of different yielding strategies. */

struct vrt_yield_strategy {
    /** Yields control to other producers and consumers. */
    int
    (*yield)(struct vrt_yield_strategy *self, bool first,
             const char *queue_name, const char *name);

    /** Frees this yield strategy. */
    void
    (*free)(struct vrt_yield_strategy *self);
};

#define vrt_yield_strategy_yield(self, first, qn, n) \
    ((self)->yield((self), (first), (qn), (n)))

#define vrt_yield_strategy_free(self) \
    ((self)->free((self)))

/* A yield strategy that simply does a spin-loop.  (Only works if each
 * producer/consumer is in a separate thread.) */
struct vrt_yield_strategy *
vrt_yield_strategy_spin_wait(void);

/* A yield strategy that simply does a short spin-loop and then yields
 * to other threads.  (Only works if each producer/consumer is in a
 * separate thread.) */
struct vrt_yield_strategy *
vrt_yield_strategy_threaded(void);

/* A yield strategy that yields to other coroutines within the same
 * thread for the first couple of waits, and then falls back on
 * progressively more intense yields. */
struct vrt_yield_strategy *
vrt_yield_strategy_hybrid(void);

#ifdef __cplusplus
}
#endif

#endif /* VRT_YIELD_H */
