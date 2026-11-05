#ifndef DW4_NPCMOTION_H
#define DW4_NPCMOTION_H
#include "eefloat.h"
/* beModelCtrlMoveObject layout; bit-pattern floats retain EE arithmetic.
 * Retail start/expire/update: 0x00392d20 / 0x00392d90 / 0x00392e10. */
typedef struct {
    uint32_t reserved[2];
    uint8_t active, pad[3];
    ee_f32 time;
    int32_t mode;
    ee_f32 value, acceleration, speed;
    uint8_t seq_stop, pad2[3];
    ee_f32 stop_value, stop_frame;
} dw4_npc_motion;
void dw4_npc_motion_start(dw4_npc_motion *, ee_f32 value, ee_f32 frame,
                          ee_f32 time, int mode);
void dw4_npc_motion_expire(dw4_npc_motion *);
ee_f32 dw4_npc_motion_tick(dw4_npc_motion *, ee_f32 delta);
#endif
