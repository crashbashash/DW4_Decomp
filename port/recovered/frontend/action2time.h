/* recovered/frontend/action2time.h -- beAction2 timing/completion slice.
 *
 * Behavioral recovery of the retail code that decides when a model-controller
 * ACTION finishes.  Executable references, not newly byte-matched units.
 *
 *   0x00230110  a2_f32_to_s64         float -> int64 (via ee_f32_to_s64)
 *   0x00398e80  a2_node_time          node clock: scale * (clock>>18), re-biased
 *   0x003a7a20  a2_timer_start        arm/restart the named "WAIT" timer
 *   0x003a7d00  a2_ref_release        smart-pointer style release + optional delete
 *   0x003a7d80  a2_timer_exists
 *   0x003a7e90  a2_timer_complete     duration <  elapsed  (strict, signed 64-bit)
 *   0x003a7fd0  a2_timer_elapsed
 *   0x00376340  a2_waitcheck_update   beAction2WAITCHECK_Update
 *   0x003764c0  a2_waitcheck_start    beAction2WAITCHECK_Start
 *   0x00376de0  a2_jointset_update    beAction2JOINTSET_Update
 *   0x00376f40  a2_jointset_start     beAction2JOINTSET_Start
 *   0x00377700  a2_start_components   beAction2_StartComponents
 *   0x003778d0  a2_update             Gap::Bec::beAction2::vfunc_31 (per frame)
 *   0x00377990  a2_msg_iscomend       vfunc_33, message case 0 ("ISCOMEND") only
 *
 * `mgr` is the Gap::Bec::beAction2 manager (a0 of every handler); `act` is the
 * playing-action object (a1: +8 bit index, +0xc beAction2Data, +0x14 active,
 * +0x28 property list, +0x2c time node, +0x38 beAction2InfoWork).  mgr+0xc is
 * the engine system whose int64 clock lives at +0x50 and whose unit is
 * nanoseconds; mgr+0x14 is the messenger.
 *
 * Lower-engine boundaries (everything else here is recovered): property-list
 * lookup/insert, object allocation, string interning, the FADESET/MOTIONSET/
 * FLASHSET handlers, the ACTION message plumbing, the 0x1dd4b0/0x1af510 motion
 * clock helpers, and the *source of the system clock value itself*.
 */
#ifndef DW4_ACTION2TIME_H
#define DW4_ACTION2TIME_H
#include "eefloat.h"
#include "loadintf2.h"

/* The shared peek/poke/call plus a 64-bit-argument call: two leaves take
 * int64 registers (0x1dd4b0, 0x1af510).  `base.call` truncates to 32 bits. */
typedef struct {
    Dw4LoadIntf2Api base;
    int32_t (*call64)(void *user, int32_t addr, const int64_t a[8]);
} Dw4Action2Api;

enum {
    A2_TIMER_NAME     = 0x50dfd8,   /* "WAIT": name of the timer property      */
    A2_STR_EMPTY      = 0x4e0858,
    A2_GP_FLAG        = 0x554c14,   /* gp-31836: allocator-selection flag       */
    A2_POOL_ROOT      = 0x587110,
    A2_PROP_TYPE      = 0x585be0,   /* lookup key argument of 0x003022c0        */
    A2_RHYTHM_GLOBAL  = 0x58a348,   /* f32 stored by "R??S" WAITCHECK           */
    A2_CLASS_MOTIONSET= 0x589fe8, A2_CLASS_JOINTSET = 0x589fc8,
    A2_CLASS_FADESET  = 0x589fb0, A2_CLASS_WAITCHECK = 0x589fa0,
    A2_CLASS_FLASHSET = 0x589f98,
    /* Scratch standing in for the retail stack out-parameter of 0x1dd4b0. */
    A2_SCRATCH        = 0x01060000
};
/* Timer property fields (+0x10 f32 scale, +0x18 i64 base, +0x20 i64
 * duration, +0x28 i64 start clock, +0x38 f32 1.0). */
enum { A2_T_SCALE=0x10, A2_T_BASE=0x18, A2_T_DURATION=0x20, A2_T_START=0x28, A2_T_ONE=0x38 };
/* beAction2InfoWork fields. */
enum { A2_W_COMDATA=0x08, A2_W_COMINDEX=0x0c, A2_W_MOTION=0x14, A2_W_JOINT=0x1c,
       A2_W_JSTART=0x20, A2_W_JEND=0x28, A2_W_JISEND=0x30, A2_W_FADE=0x34,
       A2_W_WAIT=0x44, A2_W_FLASH=0x48, A2_W_FREEZE=0x4c };
/* WAITCHECK work states (work+0x44). */
enum { A2_WAIT_NONE=0, A2_WAIT_FRAME=1, A2_WAIT_MOTION=2, A2_WAIT_JOINT=3 };
/* beModelCtrlNode2: +0x78 f32 time scale, +0x80 i64 time bias. */
enum { A2_N_SCALE=0x78, A2_N_BIAS=0x80 };

int64_t a2_f32_to_s64(ee_f32);
int64_t a2_node_time(const Dw4Action2Api *, int32_t node, int64_t clock);
void    a2_timer_start(const Dw4Action2Api *, int32_t act, int32_t name, int64_t duration);
int32_t a2_ref_release(const Dw4Action2Api *, int32_t ref, int32_t flags);
int32_t a2_timer_exists(const Dw4Action2Api *, int32_t act, int32_t name);
int32_t a2_timer_complete(const Dw4Action2Api *, int32_t act, int32_t name);
int64_t a2_timer_elapsed(const Dw4Action2Api *, int32_t act, int32_t name);
void    a2_waitcheck_update(const Dw4Action2Api *, int32_t mgr, int32_t act);
int32_t a2_waitcheck_start(const Dw4Action2Api *, int32_t mgr, int32_t act, int32_t comp);
void    a2_jointset_update(const Dw4Action2Api *, int32_t mgr, int32_t act);
int32_t a2_jointset_start(const Dw4Action2Api *, int32_t mgr, int32_t act, int32_t comp);
void    a2_start_components(const Dw4Action2Api *, int32_t mgr, int32_t act);
void    a2_update(const Dw4Action2Api *, int32_t mgr, int32_t act);
int32_t a2_msg_iscomend(const Dw4Action2Api *, int32_t mgr, int32_t act, int32_t msg);
#endif
