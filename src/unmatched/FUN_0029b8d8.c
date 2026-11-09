typedef struct SfdCopyChunk {
    int addr;
    int size;
} SfdCopyChunk;

typedef struct SfdCopyCtx {
    int f0;
    int buf;
    int f8;
    char pad12[60];
    int total;
} SfdCopyCtx;

typedef struct SfdCopyStream {
    char pad[8188];
    SfdCopyCtx * ctx;
} SfdCopyStream;

void FUN_0028b0c0(int src, int dst, int n);
void FUN_0029b820(int buf, int arg, SfdCopyChunk *chunk);
void FUN_0029b850(int buf, int n, SfdCopyChunk *chunk);

void FUN_0029b8d8(SfdCopyStream *obj, int dst, int max, int *out)
{
    SfdCopyCtx *ctx = obj->ctx;
    int buf = ctx->buf;
    SfdCopyChunk chunk;
    int n;

    FUN_0029b820(buf, ctx->f8, &chunk);
    n = chunk.size;
    if (max < n)
        n = max;
    if (n > 0x19000)
        n = 0x19000;
    FUN_0028b0c0(chunk.addr, dst, n);
    FUN_0029b850(buf, n, &chunk);
    ctx->total += n;
    *out = n;
}
