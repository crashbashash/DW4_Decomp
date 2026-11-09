typedef struct SfdCtlPair {
    long long a;
    long long b;
} SfdCtlPair;

typedef struct SfdCtlCtx {
    int handle;
    char pad4[44];
    int carry;
} SfdCtlCtx;

typedef struct SfdCtlStream {
    char pad[4120];
    char sub[4068];
    SfdCtlCtx *ctx;
} SfdCtlStream;

int FUN_0026c328(int handle);
int FUN_0026d048(int handle, int pos);
int FUN_0029c470(int handle);
void FUN_0029ccd0(SfdCtlStream *obj, unsigned int mode);
void FUN_0029cd58(SfdCtlStream *obj, int *pos, int size);
void FUN_002b05b0(void *sub, SfdCtlPair *pair);

/* matching construct: permuter, reduced by hand: the carry stored last */
int FUN_0029cb90(SfdCtlStream *obj, unsigned int mode)
{
    SfdCtlCtx *ctx;
    int handle;
    int size;
    int pos;
    int at;
    int carry;
    SfdCtlPair pair;

    ctx = obj->ctx;
    handle = ctx->handle;
    switch (mode) {
    case 0:
        ctx->carry = 0;
        FUN_0029ccd0(obj, 0);
        break;
    case 1:
        FUN_0029ccd0(obj, 1);
        break;
    case 2:
        if (FUN_0029c470(handle) == 0)
            break;
        size = FUN_0026c328(handle);
        FUN_0029cd58(obj, &pos, size);
        at = pos + ctx->carry;
        carry = at - FUN_0026d048(handle, at);
        pair.a = pos;
        pair.b = size;
        ctx->carry = carry;
        FUN_002b05b0(obj->sub, &pair);
        break;
    }
    return 0;
}
