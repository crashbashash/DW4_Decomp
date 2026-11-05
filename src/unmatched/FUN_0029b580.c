/* 0x0029b580 — FUN_0029b580 (88 bytes). Copies a seven-word buffer configuration into DAT_0057fa90, rounding the two sizes up to 32 bytes. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Seven-word buffer configuration: pointer-typed words and two byte sizes (+8, +24).
 * The pointer/int split is what lets the scheduler reorder the loads and stores the way retail does. */
struct BufConfig {
    void *f0;
    void *f4;
    int f8;                               /* size, rounded up to 32 bytes when stored */
    void *f12;
    void *f16;
    void *f20;
    int f24;                              /* size, rounded up to 32 bytes when stored */
};
extern struct BufConfig DAT_0057fa90;

void FUN_0029b580(struct BufConfig *config) {
    DAT_0057fa90.f0 = config->f0;
    DAT_0057fa90.f8 = (config->f8 + 31) & ~31;
    DAT_0057fa90.f4 = config->f4;
    DAT_0057fa90.f12 = config->f12;
    DAT_0057fa90.f24 = (config->f24 + 31) & ~31;
    DAT_0057fa90.f16 = config->f16;
    DAT_0057fa90.f20 = config->f20;
}
