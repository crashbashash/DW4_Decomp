#include "dw4/cri/sfx.h"

typedef struct SfxZLib {
    int nhn;
    int f4;
    int maxhn;
    SfxZHn hn[8];
} SfxZLib;

extern SfxZLib DAT_004bf010;

extern char DAT_004f5870[];
extern char DAT_004f5878[];
extern char DAT_004f5880[];
extern char DAT_004f5888[];
extern char DAT_004f5890[];
extern char DAT_004f5898[];
extern char DAT_004f58a0[];
extern char DAT_004f58b0[];
extern char DAT_004f58f0[];
extern char DAT_004f5920[];
extern char DAT_004f5928[];
extern char DAT_004f5958[];
extern char DAT_004f5990[];

void *memset(void *dst, int value, unsigned int size);
int sscanf(const char *s, const char *fmt, ...);
long long __muldi3(long long n, int k);
int FUN_0027d6b0(SfxMem *in, char *tag, char *endtag, SfxMem *out);
int FUN_002b3780(SfxFrame *frm, char *tag);

void FUN_002b4228(void);
SfxZHn *FUN_002b42c8(void);
void FUN_002b4318(SfxZHn *zhn);
void FUN_002b4380(SfxZHn *zhn);
void FUN_002b45b0(SfxZHn *zhn, char *tag, char *endtag, char **data, int *size);
void FUN_002b4648(SfxZHn *zhn, int lo, int hi, unsigned int *tbl);
void FUN_002b47d8(SfxZHn *zhn, int lo, int hi, unsigned int *buf);
void FUN_002b48d0(SfxZHn *zhn, unsigned int *src, short *dst);
void FUN_002b4960(SfxZHn *zhn, unsigned int *src, unsigned int *dst);
int FUN_002b4b10(float zmin, float zmax);
int FUN_002b4b58(SfxZHn *zhn);
void FUN_002b4b88(int value);
int FUN_002b4b98(void);
void FUN_002b4c98(SfxHn *hn, SfxFrame *frm, int zbit, int arg);
void FUN_002b4dc8(SfxHn *hn, SfxFrame *frm, int zbit, int arg);
void FUN_002b4f58(SfxHn *hn, SfxFrame *frm, int zbit, int arg);
int FUN_002b5068(int zbit);
SfxZHn *FUN_002b50c8(SfxHn *hn, int zbit);

void FUN_002b4210(void) {
    FUN_002b4228();
}

void FUN_002b4228(void) {
    memset(&DAT_004bf010, 0, 0x26C);
    DAT_004bf010.maxhn = 8;
    FUN_002b4b88(0);
}

void FUN_002b4268(void)
{
}

SfxZHn *FUN_002b4270(void) {
    SfxZHn *zhn = FUN_002b42c8();
    if (zhn == 0) {
        return 0;
    }
    FUN_002b4318(zhn);
    DAT_004bf010.nhn++;
    zhn->used = 1;
    return zhn;
}

/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void FUN_002b4318(SfxZHn *zhn) {
    zhn->zmin = 0;
    zhn->zmax = 0;
    zhn->cbfn = 0;
    zhn->cbarg = 0;
    zhn->zbit = 0;
}

/* matching construct: manual — the in-use word is written through a volatile pointer; retail leaves the branch delay slot empty */
void FUN_002b4330(volatile SfxZHn *zhn) {
    if (zhn != 0) {
        zhn->used = 0;
        DAT_004bf010.nhn--;
    }
}

void FUN_002b4358(SfxZHn *zhn, char *data, int size) {
    SfxChunk *info = &zhn->info;
    info->valid = 1;
    info->data = data;
    info->size = size;
    FUN_002b4380(zhn);
}

void FUN_002b4380(SfxZHn *zhn) {
    SfxChunk *hdr = &zhn->hdr;
    SfxChunk *vfrm = &zhn->vfrm;
    SfxChunk *info = &zhn->info;
    SfxMem in;
    SfxMem out;
    if (info->data == 0) {
        hdr->size = 0;
        hdr->valid = 1;
        hdr->data = 0;
        vfrm->valid = 1;
        vfrm->data = 0;
        vfrm->size = 0;
        return;
    }
    in.data = info->data;
    in.size = info->size;
    FUN_0027d6b0(&in, DAT_004f5870, DAT_004f5878, &out);
    hdr->data = out.data;
    hdr->size = out.size;
    hdr->valid = 1;
    FUN_0027d6b0(&in, DAT_004f5880, DAT_004f5878, &out);
    vfrm->valid = 1;
    vfrm->data = out.data;
    vfrm->size = out.size;
}

void FUN_002b4468(SfxZHn *zhn, char **data, int *size) {
    SfxChunk *info = &zhn->info;
    char *value4;
    int value8;
    if (info->valid != 1) {
        *data = 0;
        *size = 0;
        return;
    }
    value4 = info->data;
    value8 = info->size;
    *size = value8;
    *data = value4;
}

void FUN_002b4498(SfxZHn *zhn, int frame, int *first, int *second) {
    char *p;
    int len;
    long long n;
    long long x, y, z;
    char *str;
    FUN_002b45b0(zhn, DAT_004f5888, DAT_004f5878, &p, &len);
    if (p == 0) {
        *first = 0;
        *second = 0x7FFFFFFF;
        return;
    }
    sscanf(p, DAT_004f5890, &n);
    FUN_002b45b0(zhn, DAT_004f5898, DAT_004f5878, &p, &len);
    str = p;
    if (str == 0) {
        *first = 0x7FFFFFFF;
        return;
    }
    sscanf(str + (int)__muldi3(n, frame), DAT_004f58a0, &x, &y, &z);
    *first = y;
    *second = z;
}

void FUN_002b4630(SfxZHn *zhn, int lo, int hi, unsigned int *tbl) {
    FUN_002b4648(zhn, lo, hi, tbl);
}

void FUN_002b4648(SfxZHn *zhn, int lo, int hi, unsigned int *tbl)
{
    int i;
    if (hi == (int)0x80000000)
        hi = 0x7FFFFFFF;
    if (lo == (int)0x80000000)
        lo = 0x7FFFFFFF;
    for (i = 8; i >= 0; i--)
        tbl[i] = 0;
    for (i = 9; i < 17; i++)
        tbl[i] = lo;
    if (lo == hi) {
        for (i = 17; i < 224; i++)
            tbl[i] = lo;
    } else {
        for (i = 17; i < 224; i++)
            tbl[i] = (unsigned int)(hi - lo) / 207 * (i - 17) + lo;
    }
    for (i = 224; i < 240; i++)
        tbl[i] = hi;
    for (i = 240; i < 256; i++)
        tbl[i] = 0x7FFFFFFF;
}

void FUN_002b4788(SfxZHn *zhn, int frame, unsigned int *buf) {
    int first;
    int second;
    FUN_002b4498(zhn, frame, &first, &second);
    FUN_002b47d8(zhn, first, second, buf);
}

void FUN_002b47d8(SfxZHn *zhn, int lo, int hi, unsigned int *buf) {
    unsigned int *tbl = buf + 0x100;
    SfxZCbFn cbfn;
    memset(buf, 0, 0x400);
    FUN_002b4630(zhn, lo, hi, tbl);
    cbfn = zhn->cbfn;
    if (cbfn == 0) {
        if (zhn->zbit == 16) {
            FUN_002b48d0(zhn, tbl, (short *)buf);
            return;
        }
        FUN_002b4960(zhn, tbl, buf);
        return;
    }
    cbfn(tbl, buf, zhn->zmin, zhn->zmax);
}

void FUN_002b48d0(SfxZHn *zhn, unsigned int *src, short *dst) {
    int i;
    if (FUN_002b4b98() == 1) {
        for (i = 0; i < 256; i++) {
            dst[i] = src[i] >> 15;
        }
    } else {
        FUN_002b3b38(0, 0, DAT_004f58b0);
    }
}

void FUN_002b4960(SfxZHn *zhn, unsigned int *src, unsigned int *dst)
{
    float scale = zhn->zmax;
    int i;
    unsigned int v;
    if (FUN_002b4b98() == 1) {
        for (i = 0; i < 256; i++)
            dst[i] = (src[i] & 0x7FFFFF80) * 2;
        return;
    }
    for (i = 0; i < 256; i++) {
        if (src[i] == 0)
            src[i] = 1;
        v = src[i];
        dst[i] = 16777215.0f / (scale * v / 2147483520.0f);
    }
}

void FUN_002b4aa8(SfxZHn *zhn, float zmin, float zmax) {
    if (FUN_002b4b10(zmin, zmax) != 1) {
        FUN_002b3b38(0, 0, DAT_004f58f0);
    }
    zhn->zmin = zmin;
    zhn->zmax = zmax;
}

int FUN_002b4b10(float zmin, float zmax) {
    int var_v0;
    var_v0 = 1;
    if (zmax <= zmin) {
        var_v0 = 0;
    }
    if ((zmax - zmin) < -14.0f) {
        var_v0 = 0;
    }
    return var_v0;
}

void FUN_002b4b40(SfxZHn *zhn, float *zmin, float *zmax) {
    *zmin = zhn->zmin;
    *zmax = zhn->zmax;
}

int FUN_002b4b58(SfxZHn *zhn) {
    float a = zhn->zmin;
    float b = zhn->zmax;
    int nonzero = 1;
    if (a == 0.0f && b == 0.0f) {
        nonzero = 0;
    }
    return nonzero;
}

void FUN_002b4b88(int value) {
    DAT_004bf010.f4 = value;
}

int FUN_002b4b98(void) {
    return DAT_004bf010.f4;
}

void FUN_002b4ba8(SfxHn *hn, SfxFrame *frm, int arg) {
    FUN_002b50c8(hn, 16);
    FUN_002b4c98(hn, frm, 16, arg);
}

void FUN_002b4bf8(SfxHn *hn, SfxFrame *frm, int arg) {
    FUN_002b50c8(hn, 24);
    FUN_002b4c98(hn, frm, 24, arg);
}

void FUN_002b4c48(SfxHn *hn, SfxFrame *frm, int arg) {
    FUN_002b50c8(hn, 32);
    FUN_002b4c98(hn, frm, 32, arg);
}

void FUN_002b4c98(SfxHn *hn, SfxFrame *frm, int zbit, int arg) {
    if (hn->compo == 0) {
        hn->compo = FUN_002b3780(frm, DAT_004f5920);
    }
    if (FUN_002b4b58(hn->zhn) != 1) {
        FUN_002b3b38(hn, frm, DAT_004f5928);
        return;
    }
    switch (frm->frmfmt) {
    case 3:
        FUN_002b4dc8(hn, frm, zbit, arg);
        return;
    case 2:
        FUN_002b4f58(hn, frm, zbit, arg);
        return;
    case 1:
    default:
        FUN_002b3b38(hn, frm, DAT_004f5958);
        return;
    }
}

int FUN_002b5068(int zbit) {
    int r;
    switch ((unsigned int)zbit) {
    case 16: r = 1; break;
    case 24: r = 2; break;
    case 32: r = 3; break;
    case 8:
    default:
        FUN_002b3b38(0, 0, DAT_004f5990);
        r = 0;
        break;
    }
    return r;
}

/* The pointer must live in v0, so it is returned rather than discarded. */
SfxZHn *FUN_002b50c8(SfxHn *hn, int zbit) {
    SfxZHn *zhn = hn->zhn;
    zhn->zbit = zbit;
    return zhn;
}

int FUN_002b50d8(SfxHn *hn) {
    return hn->zhn->zbit;
}
