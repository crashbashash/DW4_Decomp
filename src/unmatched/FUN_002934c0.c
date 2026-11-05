/* 0x002934c0 — FUN_002934c0 (72 bytes). Installs the three allocator hooks in the work area from FUN_00294a30: +40 and +44 are called back as (ctx, ...) with the +48 context (FUN_00293670 releases a block through +44). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    char pad0[40];
    void *allocFn;   /* 40 */
    void *releaseFn; /* 44: called as releaseFn(ctx, block) by FUN_00293670 */
    void *ctx;       /* 48 */
} Work2934c0;
extern Work2934c0 *FUN_00294a30(void);

void FUN_002934c0(void *allocFn, void *releaseFn, void *ctx) {
    Work2934c0 *work = FUN_00294a30();

    work->allocFn = allocFn;
    work->releaseFn = releaseFn;
    work->ctx = ctx;
}
