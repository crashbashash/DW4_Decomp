#ifndef DW4_ACTION2HOST_H
#define DW4_ACTION2HOST_H
#include "action2time.h"
#include "dw4/random.h"
#include "dw4/arena.h"
/* DW4_A2_IMAGE_COMPONENTS records fit the oracle image; DW4_A2_MAX_COMPONENTS is the host's capacity. The longest authored action in the retail
 * packs has 24 components (the item and pickup FLASH1 blink-outs), so the records past the image live beyond it, in mapped objects only. */
enum { DW4_A2_BASE=0x1500000, DW4_A2_BYTES=0x2000, DW4_A2_IMAGE_COMPONENTS=16, DW4_A2_MAX_COMPONENTS=32 };
/* DW4_A2_MOTIONSET is the fourth component class the recovered walk starts (0x377340): it starts the named animation when the walk reaches it, so a
 * WAITCHECK Motion between two MOTIONSETs holds the second one back until the first has played out. */
enum { DW4_A2_FADESET=1, DW4_A2_JOINTSET, DW4_A2_WAITCHECK, DW4_A2_MOTIONSET };
typedef struct {
    int kind;
    const char *name;
    uint32_t first, last;
    const char *loop;
    int64_t duration, blend;   /* MOTIONSET only: the animation's length and the blend-in time, both in Action2 time units (0 for the other classes) */
} dw4_action2_component;
/* The fixed addresses belong only to the recovered-rule adapter. Reflected
 * records, list entries and strings live in the session arena; their actual
 * fields hold handles. Host storage contains service stubs and render events. */
typedef struct {
    int address;uint32_t size;dw4_handle object;uint64_t references;
    int is_object,kind;
} dw4_action2_mapping;
typedef struct {
    dw4_arena *arena;dw4_handle manager,info,ram,work,node,data,timer,motion,animation,previous_motion,previous_animation;
} dw4_action2_record;
typedef struct {
    unsigned char backend[DW4_A2_BYTES];
    dw4_arena *arena;dw4_action2_mapping mapping[160];unsigned mapped,roots;
    int done,error;
    int fade_in,fade_out,joint_first,joint_last;
    int hidden; /* FADESET HIDE clears model eligibility; IN/OUT restore it. */
    int motion_loop; /* Native sampler mode; full Alchemy blending remains a backend. */
    unsigned fade_serial;
    int fade_direction,fade_frames;
    /* Every FADESET the rule starts (IN, OUT and HIDE) bumps fade_event and leaves its kind letter and raw frames / limit float words: a fade that starts after a
     * WAITCHECK (the items' blink-out restarts ten fade-outs) is applied when the host reaches it, not when the action begins. */
    unsigned fade_event;int fade_kind;uint32_t fade_first_bits,fade_limit_bits;
    Dw4Action2Api api;
    void *oracle_user;
    void (*invoke)(void *,int,const Dw4Action2Api *,const int32_t[3]);
    dw4_random *random;
    uint32_t *rhythm;
    int64_t motion_start,blend_end;   /* the latest MOTIONSET's start and the time its blend ends (0: no blend pending): until then the combiner holds two states */
    int64_t clock;   /* the clock of the latest start/tick: the time a MOTIONSET the walk reaches starts at */
    struct {int64_t duration,blend;} motionset[DW4_A2_MAX_COMPONENTS];   /* per component slot, from the started program */
} dw4_action2_host;
/* Borrow the one engine stream and shared WAITCHECK rhythm value. */
void dw4_action2_host_random(dw4_action2_host *,dw4_random *,uint32_t *rhythm);
/* Fresh init only; close before reuse. Allocation failure sets error. */
void dw4_action2_host_init(dw4_action2_host *);
void dw4_action2_host_close(dw4_action2_host *);
/* Name belongs to the selected typed action data; NULL clears selection. */
int dw4_action2_host_set_name(dw4_action2_host *,const char *);
const char *dw4_action2_host_name(const dw4_action2_host *);
int dw4_action2_host_started(const dw4_action2_host *);
int dw4_action2_host_timer_present(const dw4_action2_host *);
/* Borrowed handles: the complete closure belongs to this host until close. */
dw4_action2_record dw4_action2_host_records(const dw4_action2_host *);
/* Canonical adapter image for the retail oracle; arena addresses are normalized. */
void dw4_action2_host_snapshot(const dw4_action2_host *,unsigned char out[DW4_A2_BYTES]);
void dw4_action2_host_motion(dw4_action2_host *,int64_t start,int64_t duration,int loop);
/* Current/previous sampler names and blend duration belong to animation records. A blend > 0 over a previous motion keeps the combiner at two states until start + blend
 * (the WAITCHECK Motion cannot end earlier). */
int dw4_action2_host_motion_name(dw4_action2_host *,const char *,int64_t blend);
void dw4_action2_host_start(dw4_action2_host *,int action,int64_t clock);
/* Components are copied; borrowed strings need survive only this call. */
void dw4_action2_host_start_program(dw4_action2_host *, const dw4_action2_component *,
                                    unsigned count, int64_t clock);
int64_t dw4_action2_host_node_time(const dw4_action2_host *, int64_t clock);
int dw4_action2_host_tick(dw4_action2_host *,int64_t clock);
#endif
