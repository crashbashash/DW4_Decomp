typedef struct ErrCtx {
    int handle;
    char pad4[68];
    int f72;
} ErrCtx;

typedef struct ErrStream {
    char pad[4120];
    char sub[4068];
    int ctx;
} ErrStream;

extern int DAT_0057faac;
int FUN_0026bd20(int handle);
int FUN_0026cce0(int handle);
void FUN_0026cfe8(int handle);
int FUN_0029c368(ErrStream *obj);
void FUN_0029c398(ErrStream *obj, int on);
int FUN_002a0bb8(ErrStream *obj, int code);
int FUN_002adc40(ErrStream *obj, int id);
void FUN_002b05a8(void *sub, int a);

void FUN_0029c0b8(ErrStream *obj, int flag)
{
    ErrCtx *ctx = (ErrCtx *)obj->ctx;
    int handle = ctx->handle;
    void *sub = obj->sub;
    int st;
    int err;

    st = FUN_0026bd20(handle);
    err = FUN_0026cce0(handle);
    if (err != 0)
        DAT_0057faac = err;
    if (FUN_002adc40(obj, 26) == 0)
        err = 0;
    switch (err) {
    case 0:
        break;
    case -1:
        FUN_002a0bb8(obj, 0xFF000C08);
        break;
    case -2:
        FUN_002a0bb8(obj, 0xFF000C09);
        break;
    default:
        FUN_002a0bb8(obj, 0xFF000C07);
        break;
    }
    if (st == 4 || st == 5)
        FUN_002b05a8(sub, 0);
    if (st == 5 || err != 0)
        FUN_0029c398(obj, 1);
    if (FUN_0029c368(obj) != 1 || flag != 0)
        return;
    FUN_0026cfe8(handle);
    if (ctx->f72 != 0)
        return;
    FUN_0029c398(obj, 1);
}
