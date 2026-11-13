/* Installs the three allocator hooks in the work area from mwsfd_GetWork: +40 and +44 are called
 * back as (ctx, ...) with the +48 context (FUN_00293670 releases a block through +44). */
typedef struct {
    char pad0[40];
    void *allocFn;   /* 40 */
    void *releaseFn; /* 44: called as releaseFn(ctx, block) by FUN_00293670 */
    void *ctx;       /* 48 */
} Work2934c0;
extern Work2934c0 *mwsfd_GetWork(void);

void MWSFD_SetMallocFunc(void *allocFn, void *releaseFn, void *ctx) {
    Work2934c0 *work = mwsfd_GetWork();

    work->allocFn = allocFn;
    work->releaseFn = releaseFn;
    work->ctx = ctx;
}
