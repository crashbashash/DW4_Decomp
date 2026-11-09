typedef struct SfdStartInfo {
    int valid;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
} SfdStartInfo;

typedef struct SfdStartCtx {
    int handle;
    char pad4[48];
    int started;
    int f56;
    int (*step)();
} SfdStartCtx;

typedef struct SfdStartStream {
    char pad[8188];
    SfdStartCtx * ctx;
} SfdStartStream;

void FUN_00263548(int handle, int a, int b, int c);
void FUN_0026d138(int handle, int flag);
SfdStartInfo *FUN_0029ceb8(SfdStartStream *obj);
int FUN_0029be80();

int FUN_0029ce28(SfdStartStream *obj)
{
    SfdStartInfo *info;
    SfdStartCtx *ctx;
    int handle;
    int ret;

    info = FUN_0029ceb8(obj);
    if (info == 0)
        return 0;
    ctx = obj->ctx;
    handle = ctx->handle;
    if (ctx->started != 0)
        return 0;
    if (info->valid == 0)
        return 0;
    FUN_00263548(handle, info->f12, info->f16, info->f20);
    FUN_0026d138(handle, 0);
    ctx->started = 1;
    ctx->step = FUN_0029be80;
    return 0;

}
