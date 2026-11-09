typedef struct SfdFeedCtx {
    char pad[60];
    int (*step)();
} SfdFeedCtx;

typedef struct SfdFeedStream {
    char pad[2496];
    long long total;
    char pad2504[5684];
    int ctx;
} SfdFeedStream;

int FUN_0026d250(char *buf, int size, int *len);
char *FUN_0029bd60(SfdFeedStream *obj, char *buf, int size);
int FUN_002a0928(SfdFeedStream *obj);
int FUN_0029b990();

void FUN_0029bca0(SfdFeedStream *obj, char *buf, int size, int *used)
{
    SfdFeedCtx *ctx;
    int len;
    int n;

    *used = 0;
    ctx = (SfdFeedCtx *)obj->ctx;
    if (size < 288)
        return;
    if (FUN_0026d250(buf, size, &len) != 0)
        n = len;
    else if (FUN_002a0928(obj) < 108)
        n = FUN_0029bd60(obj, buf, size) - buf;
    else
        n = 0;
    *used = n;
    ctx->step = FUN_0029b990;
    obj->total += n;
}
