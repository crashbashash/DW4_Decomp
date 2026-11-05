/* 0x0025b9e8 — FUN_0025b9e8 (44 bytes). Calls the hook in D_00498a40 when the context's handle at +192 is set. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Ctx25b9e8 { char pad[192]; void *handle; } Ctx25b9e8;
extern void (*D_00498a40)(void);

void FUN_0025b9e8(Ctx25b9e8 *ctx) {
    if (ctx->handle) {
        D_00498a40();
    }
}
