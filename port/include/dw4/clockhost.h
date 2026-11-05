/* Bounded native storage for the unchanged recovered timer/system clock.
 * Initialization and raw source cadence are host policy, not recovered defaults. */
#ifndef DW4_CLOCKHOST_H
#define DW4_CLOCKHOST_H
#include "systemclock.h"
enum { DW4_CLOCK_BASE=0x1600000, DW4_CLOCK_BYTES=0x800 };
typedef struct {
    unsigned char memory[DW4_CLOCK_BYTES];
    uint64_t raw;
    int external, error;
    Dw4SystemClockApi api;
    void *user;
    void (*update)(void *);
    /* Optional instruction-oracle replacement, used by differential tests. */
    uint64_t (*invoke)(void *,uint32_t,const Dw4SystemClockApi *,uint64_t,uint64_t);
    void *oracle_user;
} dw4_clock_host;
void dw4_clock_host_init(dw4_clock_host *,void *,void (*)(void *));
void dw4_clock_host_set_raw(dw4_clock_host *,uint64_t);
void dw4_clock_host_step(dw4_clock_host *);
void dw4_clock_host_pause(dw4_clock_host *);
void dw4_clock_host_resume(dw4_clock_host *);
void dw4_clock_host_scale(dw4_clock_host *,int32_t); /* signed 18 fractional bits */
uint64_t dw4_clock_host_world(dw4_clock_host *);
#endif
