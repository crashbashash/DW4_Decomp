/* 0x002b05b0 — FUN_002b05b0 (88 bytes). Unless paused (+12), advances the 64-bit accumulator at +296 by f304 * rate->f0 / rate->f8 (64-bit; GCC emits __muldi3 at 0x0022e440 and __divdi3). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* long is 64-bit under EE GCC; the ld/sd accesses show these members are 64-bit. */
struct Accum {
    char pad[12];
    int f12;                              /* non-zero: no advance */
    char pad16[296 - 16];
    long f296;                            /* accumulator */
    long f304;                            /* multiplier */
};

struct Ratio {
    long f0;                              /* numerator */
    long f8;                              /* denominator */
};

void FUN_002b05b0(struct Accum *acc, struct Ratio *ratio) {
    if (acc->f12 == 0) {
        acc->f296 += acc->f304 * ratio->f0 / ratio->f8;
    }
}
