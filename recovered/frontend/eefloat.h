/* recovered/frontend/eefloat.h -- Emotion Engine single-precision arithmetic.
 *
 * The Action2 timing code feeds EE `mul.s`/`div.s`/`add.s`/`cvt.s.w` results
 * into 64-bit nanosecond time, so a host `float` (round-to-nearest, IEEE) is
 * NOT equivalent: 1e9f * 30.0f is 0x50df8476 on the host and 0x50df8475 on
 * the EE.  Values are therefore carried as IEEE bit patterns and operated on
 * with integers only.  The model (documented EE behaviour; assumed, not
 * hardware-measured -- see docs/engine/action2-timing.md):
 *
 *   - rounding toward zero everywhere;
 *   - exponent 0 is zero (denormals flush, sign retained); exponent 255 is an
 *     ordinary number; overflow saturates to sign|0x7fffffff;
 *   - division by zero gives sign|0x7fffffff (including 0/0).
 */
#ifndef DW4_EEFLOAT_H
#define DW4_EEFLOAT_H
#include <stdint.h>
typedef uint32_t ee_f32;
ee_f32 ee_f32_mul(ee_f32, ee_f32);
ee_f32 ee_f32_div(ee_f32, ee_f32);
ee_f32 ee_f32_add(ee_f32, ee_f32);
ee_f32 ee_f32_sub(ee_f32, ee_f32);
ee_f32 ee_f32_from_s32(int32_t);     /* cvt.s.w */
int32_t ee_f32_trunc_s32(ee_f32);    /* cvt.w.s ("trunc.w.s"): toward zero, saturating */
int ee_f32_cmp(ee_f32, ee_f32);      /* -1/0/1; +0 == -0 == any denormal */
/* 0x00230110: float -> 64-bit integer.  Negative inputs convert |x| and negate
 * (two's complement); |x| >= 2^64 saturates the magnitude to 2^64-1. */
int64_t ee_f32_to_s64(ee_f32);
/* Unsigned 32-bit to float the way retail spells it: cvt.s.w directly below
 * 2^31, otherwise halve with a sticky low bit (srl/andi/or), convert, and add
 * the result to itself. */
ee_f32 ee_f32_from_u32(uint32_t);
/* `(float)(unsigned)(clock >> 18)`: dsra 18, keep the low 32 bits, then
 * ee_f32_from_u32. */
ee_f32 ee_f32_from_clock_ticks(int64_t clock);
#endif
