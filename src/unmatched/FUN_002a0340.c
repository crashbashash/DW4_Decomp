typedef struct PicInfoItem {
    int w[4];
} PicInfoItem;

typedef struct PicInfoOut {
    int valid;
    int major;
    int minor;
    int f12;
    char pad16[16];
    char f32[28];
    int f60;
    int f64;
    int f68;
    int f72;
    char f76[16];
    char f92[16];
} PicInfoOut;

void FUN_002a0498(PicInfoItem *h, PicInfoOut *out);
void FUN_002a0528(PicInfoItem *h, void *p);
int FUN_002a05e0(PicInfoItem *h, int lo, int hi);
void FUN_002a0658(PicInfoItem *h, int v, void *p);
void FUN_002a06f0(PicInfoItem *h, int v, void *p);
int FUN_002b19f0(PicInfoItem *h, int *out);
int FUN_002b1de0(PicInfoItem *h, int *a, int *b);
int FUN_002b22f0(PicInfoItem *h, int *c);

void FUN_002a0340(PicInfoItem *h, PicInfoOut *out)
{
    int ok;
    int major, minor;
    int c;
    int ver;

    if (FUN_002b19f0(h, &ok) == 0)
        ok = 0;
    if (ok == 0)
        return;
    if (FUN_002b1de0(h, &major, &minor) == 0) {
        major = 0;
        minor = 0;
    }
    out->major = major;
    out->minor = minor;
    ver = major * 100 + minor;
    if (FUN_002b22f0(h, &c) == 0)
        c = 0;
    if (ver < 110)
        c = -c;
    out->f12 = c;
    FUN_002a0498(h, out);
    FUN_002a0528(h, out->f32);
    out->f60 = FUN_002a05e0(h, 189, 189);
    out->f64 = FUN_002a05e0(h, 191, 191);
    out->f68 = FUN_002a05e0(h, 192, 223);
    out->f72 = FUN_002a05e0(h, 224, 239);
    FUN_002a0658(h, out->f68, out->f76);
    FUN_002a06f0(h, out->f72, out->f92);
    out->valid = 1;
}
