typedef struct {
    int handle;
    int h;
    int w;
} Ctx2a27d8;

void FUN_0028d510(int, int *, int);

void FUN_002a27d8(char *obj, int *w, int *h) {
    int buf[8];
    int i = 0;
    int maxw = 0;
    int maxh = 0;
    Ctx2a27d8 *ctx = *(Ctx2a27d8 **)(obj + 8052);
    int handle = ctx->handle;

    do {
        FUN_0028d510(handle, buf, i++);
        if (buf[2] >= maxw) {
            maxw = buf[2];
        }
        if (buf[3] >= maxh) {
            maxh = buf[3];
        }
    } while (i < 3);
    ctx->h = maxh;
    ctx->w = maxw;
    *w = maxw;
    *h = ctx->h;
}
