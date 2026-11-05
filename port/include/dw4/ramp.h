/* dw4/ramp.h — the retail volume ramp of a beCri handle fade: FUN_003a7590 arms it, FUN_003a7890 evaluates it once per frame (through
 * FUN_003a7810) over two 60-entry ease tables (0x004c8fc0 rising, 0x004c90b0 falling). Values are Emotion Engine single-precision bit
 * patterns (recovered/frontend/eefloat.h). The level it yields is in 0.1 dB units, base + volume + (int)(210 * factor) - 210, and a
 * fade to 0 ends at -999 (silence). tools/verify_ramp.py compares both entry points with the original instructions.
 */
#ifndef DW4_RAMP_H
#define DW4_RAMP_H
#include "eefloat.h"
typedef struct {
    int mode;                   /* 3 while a ramp runs, 0 when it reached its target level */
    int base;                   /* the cue's beSoundData._volume (retail Handle.offset) */
    ee_f32 cur, from, to, step; /* table position, fade endpoints, table steps per frame */
} dw4_ramp;
/* FUN_003a7590: `add` is the player's base volume. Arms the ramp and returns the first level. */
int dw4_ramp_start(dw4_ramp *r, int add, ee_f32 from, ee_f32 to, ee_f32 div);
/* FUN_003a7890: advances one frame and returns the level; mode becomes 0 on reaching the target, and a completed fade to 0 returns -999. */
int dw4_ramp_step(dw4_ramp *r, int add);
/* The two ease tables (rising or falling), 60 entries, as bit patterns. */
const ee_f32 *dw4_ramp_table(int rising);
#endif
