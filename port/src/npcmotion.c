#include "dw4/npcmotion.h"
/* Behavioral recovery of the contiguous retail movement-channel group.
 * Stop commands retain current speed. _frame is squared, not a ramp duration.
 * A timed acceleration changes to braking only when time-delta < 0. */
void dw4_npc_motion_start(dw4_npc_motion *m, ee_f32 value, ee_f32 frame,
                          ee_f32 time, int mode)
{
    m->mode = mode;
    m->value = value;
    m->acceleration = ee_f32_div(value, ee_f32_div(ee_f32_mul(frame, frame), 0x40000000));
    m->time = time;
    m->seq_stop = 0;
    if (mode == 5) m->speed = value ^ 0x80000000;
    else if (mode == 4) m->speed = value;
    m->active = 1;
}
void dw4_npc_motion_expire(dw4_npc_motion *m)
{
    m->time = 0;
    if (m->mode == 0 || m->mode == 1)
        dw4_npc_motion_start(m, m->stop_value, m->stop_frame, 0, m->mode + 2);
    else { m->active = 0; m->speed = 0; }
    m->seq_stop = 0;
}
ee_f32 dw4_npc_motion_tick(dw4_npc_motion *m, ee_f32 delta)
{
    ee_f32 v, a;
    if (!m->active) return 0;
    if (ee_f32_cmp(m->time, 0)) {
        ee_f32 remaining = ee_f32_sub(m->time, delta);
        if (ee_f32_cmp(remaining, 0) < 0) {
            dw4_npc_motion_expire(m);
            if (!m->active) return 0;
        } else m->time = remaining;
    }
    if (ee_f32_cmp(delta, 0x40400000) > 0) delta = 0x40400000;
    v = m->speed;
    a = ee_f32_mul(delta, m->acceleration);
    switch (m->mode) {
    case 0:
        v = ee_f32_add(v, a);
        if (ee_f32_cmp(v, m->value) > 0) v = m->value;
        break;
    case 1:
        v = ee_f32_sub(v, a);
        if (ee_f32_cmp(v, m->value ^ 0x80000000) < 0) v = m->value ^ 0x80000000;
        break;
    case 2: case 4:
        v = ee_f32_sub(v, a);
        if (ee_f32_cmp(v, 0) < 0) { m->active = 0; v = 0; }
        break;
    case 3: case 5:
        v = ee_f32_add(v, a);
        if (ee_f32_cmp(v, 0) > 0) { m->active = 0; v = 0; }
        break;
    }
    m->speed = v;
    return ee_f32_mul(v, delta);
}
