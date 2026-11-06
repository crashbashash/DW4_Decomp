/* Passes the context's handle at +180 to the hook in D_00498a48 when one is set. */
typedef struct Ctx25bb50 { char pad[180]; void *handle; } Ctx25bb50;
extern void (*D_00498a48)(void *);

void FUN_0025bb50(Ctx25bb50 *ctx) {
    if (ctx->handle) {
        D_00498a48(ctx->handle);
    }
}
