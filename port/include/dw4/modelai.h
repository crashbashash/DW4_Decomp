#ifndef DW4_MODELAI_H
#define DW4_MODELAI_H
#include "dw4/random.h"
#include "eefloat.h"
typedef struct { const char *sequence; ee_f32 direction,frames; int32_t limit; } dw4_model_ai_choice;
/* Retail 0x390f80: draw low four bits, choose the first absolute limit greater
 * than the draw. Call only after the target query succeeds and the timer expires. */
int dw4_model_ai_choose(dw4_random *,const dw4_model_ai_choice *,unsigned count);
unsigned dw4_model_ai_zone(ee_f32 squared_distance,const ee_f32 bounds[3]);
int64_t dw4_model_ai_duration(ee_f32 frames);
/* Retail 395750..395928: shortest-arc turn with ties choosing the negative
 * arc. Inputs and output are radians; limit is radians per elapsed frame. */
ee_f32 dw4_model_ai_turn(ee_f32 current,ee_f32 target,ee_f32 limit,ee_f32 frames);
/* Retail 3a7a20/3a7fd0 scale-one clock, with unsigned low-32 tick conversion. */
int64_t dw4_model_ai_clock(int64_t world_ns);
/* Scale-one Frame timer (3a8140), then the 3951e0 positive-only countdown.
 * previous/now are held session clock samples; repeated samples yield zero. */
ee_f32 dw4_model_frame_delta(int64_t previous,int64_t now);
ee_f32 dw4_model_muteki_tick(ee_f32 count,ee_f32 frames);
/* 391cf0: fallback CTRL consumers only run for SQ_NONE. move is -1 when
 * unchanged, otherwise the retail MOVE mode (0 acceleration, 2 stop). */
const char *dw4_model_ai_control(int control,int walking,const char *next,int *phase,int *move);
/* 3a68e0 -> 123640/11ede8/122d90: original single-precision atan2,
 * including quadrant constants and EE polynomial rounding. */
ee_f32 dw4_model_ai_direction(ee_f32 dx,ee_f32 dz,ee_f32 offset);
/* 3d22f0 locomotion yaw, with host stick +Y up and camera-world +Z basis. */
ee_f32 dw4_model_player_direction(ee_f32 x,ee_f32 y,ee_f32 camera_x,ee_f32 camera_z);
enum {DW4_FLOOR_KEEP,DW4_FLOOR_ADJUST,DW4_FLOOR_FALL};
/* 3926d0 admission after movement/waits; collision/messenger are owning leaves. */
int dw4_model_floor_response(int floor,int fall,int upward,int falling,int support,int landing,int sleeping);
/* 395b50 node-lock branch -> 190a50: preserve the parent matrix and apply
 * local XYZ offset to all four translation lanes with EE operation order. */
void dw4_model_lock_matrix(float out[16],const float parent[16],const float offset[3]);
/* 1906d0: pre-multiply the current matrix by a local matrix (row vectors). */
void dw4_model_local_matrix(float out[16],const float world[16],const float local[16]);
#endif
