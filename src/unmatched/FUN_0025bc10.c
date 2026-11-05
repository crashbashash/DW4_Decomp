/* 0x0025bc10 — FUN_0025bc10 (48 bytes). Passes the context's handle at +180 to the hook in D_00498a50 when one is set. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Ctx25bc10 { char pad[180]; void *handle; } Ctx25bc10;
extern void (*D_00498a50)(void *);

void FUN_0025bc10(Ctx25bc10 *ctx) {
    if (ctx->handle) {
        D_00498a50(ctx->handle);
    }
}
