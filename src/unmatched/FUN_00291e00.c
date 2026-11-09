typedef struct FrmBufsBufs {
    void *a;
    void *b;
} FrmBufsBufs;

typedef struct FrmBufsCfg {
    int f0;
    int f4;
    int width;
    int height;
} FrmBufsCfg;

extern int DAT_004bd248;
extern int DAT_004bd24c;
extern FrmBufsBufs DAT_005777e0;
void *FUN_00293508(int obj, int size);

/* matching construct: two orders tried: the buffer pointers read into locals first */
int FUN_00291e00(int obj, FrmBufsCfg *cfg, FrmBufsBufs *bufs)
{
    int ret = 0;
    int size[2];
    int n;
    void *a;
    void *b;

    size[1] = 0x840D0;
    n = cfg->width * cfg->height;
    size[0] = n * 9 / 2 + 10304;
    if (DAT_004bd248 != 0) {
        if (DAT_004bd248 < 2 || DAT_004bd24c < size[0] || DAT_004bd24c < size[1]) {
            bufs->a = 0;
            ret = -1;
            bufs->b = 0;
        } else {
            a = DAT_005777e0.a;
            b = DAT_005777e0.b;
            bufs->b = b;
            bufs->a = a;
        }
    } else {
        bufs->a = FUN_00293508(obj, size[0]);
        bufs->b = FUN_00293508(obj, size[1]);
    }
    if (bufs->a == 0 || bufs->b == 0)
        ret = -1;
    return ret;
}
