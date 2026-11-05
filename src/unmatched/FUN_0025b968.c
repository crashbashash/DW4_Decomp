typedef struct Ctx { char pad[192]; void *handle; } Ctx;
extern void (*D_00498a38)(void *);

void FUN_0025b968(Ctx *ctx)
{
    if (ctx->handle)
        D_00498a38(ctx->handle);
}
