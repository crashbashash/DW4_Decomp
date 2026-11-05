/* 0x0025bb80 — FUN_0025bb80 (100 bytes). Notifies the hook in D_00498a4c with the context's handle, then stores a value at +184 and its quotient by 96 at +188. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Ctx25bb80 {
    char pad[180];
    void *handle;   /* +180 */
    int value;      /* +184 */
    int value_div96;/* +188: value / 96 */
} Ctx25bb80;
extern void (*D_00498a4c)(void *);

void FUN_0025bb80(Ctx25bb80 *ctx, int value) {
    if (ctx->handle) {
        D_00498a4c(ctx->handle);
    }
    ctx->value = value;
    ctx->value_div96 = value / 96;
}
