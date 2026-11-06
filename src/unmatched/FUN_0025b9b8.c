/* Passes the context's handle at +192 to the hook in D_00498a3c when one is set. */
typedef struct Ctx25b9b8 { char pad[192]; void *handle; } Ctx25b9b8;
extern void (*D_00498a3c)(void *);

void FUN_0025b9b8(Ctx25b9b8 *ctx) {
    if (ctx->handle) {
        D_00498a3c(ctx->handle);
    }
}
