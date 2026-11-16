typedef struct CftEntry {
    short v[4];
} CftEntry;

typedef struct CftPlane {
    unsigned char *base;
    int height;
    int width;
} CftPlane;

typedef struct CftImage {
    int f0;
    int *base;
    int stride;
    int f12;
    int height;
    int width;
} CftImage;

typedef struct CftGifPacket {
    int w[0x600];
} CftGifPacket;

extern char *DAT_004bb3e8;
extern int DAT_004bb3ec;
extern int cft_ver_str;
extern CftGifPacket DAT_004bb3f8;
extern char DAT_004f2800[];
extern char *volatile DAT_00573ea8;

int *CFT_GetVersionStr(void);
void FUN_002830a8(int max);

void FUN_00283018(char *name)
{
    DAT_004bb3e8 = name;
}

char *FUN_00283028(void)
{
    return DAT_004bb3e8;
}

void FUN_00283038(int value)
{
    DAT_004bb3ec = value;
}

int FUN_00283048(void)
{
    return DAT_004bb3ec;
}

void FUN_00283058(void)
{
    DAT_00573ea8 = DAT_004f2800;
    *CFT_GetVersionStr() = 0;
    FUN_002830a8(128);
}

void CFT_Finish(void)
{
}

int *CFT_GetVersionStr(void)
{
    return &cft_ver_str;
}

void FUN_002830a8(int max)
{
    *CFT_GetVersionStr() = max;
}

int FUN_002830d0(void)
{
    return *CFT_GetVersionStr();
}

void CFT_Ycc420rgbToArgb8888(void)
{
}

void CFT_Ycc420plnToYcc422pix2(void)
{
}

void CFT_Ycc420plnToY84C44(void)
{
}

void CFT_InitYcc420mbToArgb8888(void)
{
}

void CFT_Ycc420mbToYcc422pix2(void)
{
}

void CFT_Argb420ToArgb8(void)
{
}

void CFT_Ycc420plnToA3V(void)
{
}

void CFT_Ycc420plnToA256V(void)
{
}

void CFT_Ycc420plnToZ16(void)
{
}

void CFT_Ycc420plnToZ32(void)
{
}

void CFT_Ycc420mbToZ32(void)
{
}

#define CFT_ROW(o, s, t)            \
    (o)[0] = (t)[(s)[0]];           \
    (o)[1] = (t)[(s)[4]];           \
    (o)[2] = (t)[(s)[8]];           \
    (o)[3] = (t)[(s)[12]];          \
    (o)[4] = (t)[(s)[16]];          \
    (o)[5] = (t)[(s)[20]];          \
    (o)[6] = (t)[(s)[24]];          \
    (o)[7] = (t)[(s)[28]];          \
    (o)[8] = (t)[(s)[32]];          \
    (o)[9] = (t)[(s)[36]];          \
    (o)[10] = (t)[(s)[40]];         \
    (o)[11] = (t)[(s)[44]];         \
    (o)[12] = (t)[(s)[48]];         \
    (o)[13] = (t)[(s)[52]];         \
    (o)[14] = (t)[(s)[56]];         \
    (o)[15] = (t)[(s)[60]];         \
    (s) += 64;                      \
    (o) += img->stride;

void CFT_Argb8888mbToZ32(unsigned char **src, CftImage *img, int *table)
{
    int rows = img->height / 16;
    int cols = img->width / 16;
    unsigned char *s = *src;
    int *column = img->base;
    int y, x;
    int *o;

    for (y = 0; y < rows; y++) {
        o = column;
        s += cols * 1024;
        for (x = 0; x < cols; x++) {
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
            CFT_ROW(o, s, table)
        }
        column += 16;
    }
}

void cft_MakeYccTbl(int mode, int lo, int hi, CftEntry *t)
{
    int max;
    int i;
    short y;
    short b1, b2, r0, r1;
    float c;
    float scale;
    int range;
    CftEntry *tb;
    CftEntry *tr;

    max = FUN_002830d0();
    i = 0;
    tb = t + 256;
    tr = t + 512;
    for (; i < 256; i++) {
        y = (int)((float)(i - 16) * 74.49599456787109375f + 0.5f);
        c = (float)(i - 128);
        b2 = (int)(c * 129.0879974365234375f + 0.5f);
        b1 = (int)(c * -25.0879993438720703125f + 0.5f);
        r1 = (int)(c * -52.0319976806640625f + 0.5f);
        r0 = (int)(c * 102.1439971923828125f + 0.5f);
        t[i].v[2] = y;
        t[i].v[1] = y;
        t[i].v[0] = y;
        tb[i].v[2] = b2;
        tb[i].v[1] = b1;
        tb[i].v[0] = 0;
        tb[i].v[3] = 0;
        tr[i].v[1] = r1;
        tr[i].v[0] = r0;
        tr[i].v[2] = 0;
        tr[i].v[3] = 0;
    }
    range = hi - lo;
    scale = (float)max / (float)range;
    if (mode == 1) {
        for (i = 0; i < 256; i++) {
            if (i < lo) {
                t[i].v[3] = max << 6;
            } else if (hi < i) {
                t[i].v[3] = 0;
            } else {
                t[i].v[3] = (int)((float)(range - (i - lo)) * scale) << 6;
            }
        }
    } else {
        for (i = 0; i < 256; i++) {
            if (i < lo) {
                t[i].v[3] = 0;
            } else if (hi < i) {
                t[i].v[3] = max << 6;
            } else {
                t[i].v[3] = (int)((float)(i - lo) * scale) << 6;
            }
        }
    }
}

void cft_MakeAlpha3Tbl(CftEntry *t, unsigned char alpha0, unsigned char alpha1, unsigned char alpha2)
{
    int i;
    float c;
    float f;
    short y;
    CftEntry *tb;
    CftEntry *tr;

    tb = t + 256;
    tr = t + 512;
    for (i = 0; i < 256; i++) {
        c = (float)(i - 128);
        tb[i].v[0] = 0;
        tb[i].v[2] = (int)(c * 129.0879974365234375f + 0.5f);
        tb[i].v[1] = (int)(c * -25.0879993438720703125f + 0.5f);
        tb[i].v[3] = 0;
        tr[i].v[1] = (int)(c * -52.0319976806640625f + 0.5f);
        tr[i].v[0] = (int)(c * 102.1439971923828125f + 0.5f);
        tr[i].v[2] = 0;
        tr[i].v[3] = 0;
    }
    for (i = 0; i < 9; i++) {
        t[i].v[2] = 0;
        t[i].v[1] = 0;
        t[i].v[0] = 0;
        t[i].v[3] = alpha0;
    }
    for (i = 9; i < 134; i++) {
        f = (float)i - 16.0f;
        y = (int)((f < 0.0f ? 0.0f : (255.0f < f ? 255.0f : f)) * 64.0f * (255.0f / 110.0f) + 0.5f);
        t[i].v[3] = alpha1 << 6;
        t[i].v[2] = y;
        t[i].v[1] = y;
        t[i].v[0] = y;
    }
    for (i = 134; i < 256; i++) {
        f = 251.0f - (float)i;
        y = (int)((f < 0.0f ? 0.0f : (255.0f < f ? 255.0f : f)) * 64.0f * (255.0f / 110.0f) + 0.5f);
        t[i].v[3] = alpha2 << 6;
        t[i].v[2] = y;
        t[i].v[1] = y;
        t[i].v[0] = y;
    }
}

void cft_MakeAlpha3TblBlack(CftEntry *t, unsigned char alpha0, unsigned char alpha1, unsigned char alpha2)
{
    int i;
    float c;
    float f;
    short y;
    CftEntry *tb;
    CftEntry *tr;

    tb = t + 256;
    tr = t + 512;
    for (i = 0; i < 256; i++) {
        c = (float)(i - 128);
        tb[i].v[0] = 0;
        tb[i].v[2] = (int)(c * 129.0879974365234375f + 0.5f);
        tb[i].v[1] = (int)(c * -25.0879993438720703125f + 0.5f);
        tb[i].v[3] = 0;
        tr[i].v[1] = (int)(c * -52.0319976806640625f + 0.5f);
        tr[i].v[0] = (int)(c * 102.1439971923828125f + 0.5f);
        tr[i].v[2] = 0;
        tr[i].v[3] = 0;
    }
    y = -1160;
    for (i = 0; i < 48; i++) {
        t[i].v[2] = y;
        t[i].v[1] = y;
        t[i].v[0] = y;
        t[i].v[3] = alpha0;
    }
    for (i = 48; i < 130; i++) {
        f = (float)i - 68.0f;
        y = (int)((f < 0.0f ? 0.0f : (255.0f < f ? 255.0f : f)) * 64.0f * (255.0f / 55.0f) + 0.5f);
        t[i].v[3] = alpha1 << 6;
        t[i].v[2] = y;
        t[i].v[1] = y;
        t[i].v[0] = y;
    }
    for (i = 130; i < 256; i++) {
        f = 247.0f - (float)i;
        y = (int)((f < 0.0f ? 0.0f : (255.0f < f ? 255.0f : f)) * 64.0f * (255.0f / 111.0f) + 0.5f);
        t[i].v[3] = alpha2 << 6;
        t[i].v[2] = y;
        t[i].v[1] = y;
        t[i].v[0] = y;
    }
}

void FUN_00284dc0(void)
{
}

void FUN_00284dc8(CftGifPacket *dst)
{
    *dst = DAT_004bb3f8;
}

void FUN_00284e80(CftPlane *plane)
{
    int rows = plane->height / 16;
    int cols = plane->width / 32;
    unsigned char *row = plane->base;
    unsigned char *d, *s;
    int y, x, r, c;

    for (y = 0; y < rows; y++) {
        d = row + 3;
        s = d + cols * 1024 - 1;
        for (x = 0; x < cols; x++) {
            for (r = 0; r < 16; r++) {
                for (c = 0; c < 16; c++) {
                    *d = (*s >> 1) + 1;
                    s += 4;
                    d += 4;
                }
            }
        }
        row += cols * 2048;
    }
}
