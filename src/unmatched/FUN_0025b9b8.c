/* 0x0025b9b8 — FUN_0025b9b8 (48 bytes). Passes the context's handle at +192 to the hook in D_00498a3c when one is set. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Ctx25b9b8 { char pad[192]; void *handle; } Ctx25b9b8;
extern void (*D_00498a3c)(void *);

void FUN_0025b9b8(Ctx25b9b8 *ctx) {
    if (ctx->handle) {
        D_00498a3c(ctx->handle);
    }
}
