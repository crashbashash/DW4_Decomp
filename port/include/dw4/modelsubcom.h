/* MODELCTRL subcommand records. The recovered HITBOX producer's arithmetic and
 * classification and per-update activation/removal rules. */
#ifndef DW4_MODELSUBCOM_H
#define DW4_MODELSUBCOM_H
#include "dw4/arena.h"
#include <stdint.h>
dw4_handle dw4_modelsubcom_new(dw4_arena *);
void dw4_modelsubcom_clear(dw4_arena *,dw4_handle);
void dw4_modelsubcom_close(dw4_arena *,dw4_handle);
typedef enum {DW4_SC_HITBOX=1,DW4_SC_EFFECT,DW4_SC_SOUND} dw4_modelsubcom_kind;
/* Native detach filter: finish effect/sound entries in their mixed list order. */
enum {DW4_SC_DEPENDENCIES=-1};
int dw4_modelsubcom_type(dw4_arena *,dw4_handle);
int dw4_modelsubcom_effect(dw4_arena *,dw4_handle,const char *model,const char *sequence,
    uint32_t start,const float offset[3],const float rotation[3],uint8_t sequence_dead,uint8_t follow);
int dw4_modelsubcom_sound(dw4_arena *,dw4_handle,const char *,uint32_t start);
/* 399c50 after SOUND PLAY: keep only a valid type-four handle. */
int dw4_modelsubcom_sound_result(dw4_arena *,dw4_handle,int64_t handle,int type);
/* Native service boundary for slots 21/23. start writes the retail keep byte;
 * finish ignores it. Return 1 to stop traversal after source replacement,
 * -1 for failure. The entry is retained through every callback. */
typedef int (*dw4_modelsubcom_event)(void *,dw4_handle,int finish,int *keep);
int dw4_modelsubcom_step_events(dw4_arena *,dw4_handle,uint32_t,
    dw4_modelsubcom_event,void *);
/* type=0 is sequence/REMOVE clear (399f20); otherwise class clear (39a130).
 * Sequence clear skips finish for effects whose _isSeqDead byte is zero.
 * DW4_SC_DEPENDENCIES applies class-clear finish rules to effects and sounds
 * together, preserving HITBOX records and the original mixed list order. */
int dw4_modelsubcom_clear_events(dw4_arena *,dw4_handle,int type,
    dw4_modelsubcom_event,void *);
/* Copies call-local command bits/geometry; publishes only a complete object. */
int dw4_modelsubcom_hitbox(dw4_arena *,dw4_handle,int32_t kind,
    uint32_t start,uint32_t length,const float offset[3],const float size[3]);
/* System 3a0020: signed wrapped world delta / 16666667, without the named
 * Frame timer's quantization or three-frame clamp. */
uint32_t dw4_modelsubcom_frame(int64_t previous,int64_t now);
/* Emit returns 0 to continue, 1 when a callback replaced the source sequence,
 * -1 on native delivery failure. The entry is retained during the callback;
 * callbacks may clear/replace the list but must not destroy the owner. */
typedef int (*dw4_modelsubcom_emit)(void *,dw4_handle);
int dw4_modelsubcom_step(dw4_arena *,dw4_handle,uint32_t frame,
    dw4_modelsubcom_emit,void *);
#endif
