#include "dw4/cri/sfx.h"
#include <stdio.h>
#include <string.h>
#include "dw4/cri/sj.h"
#include "dw4/support/softfloat.h"

typedef struct SfxZLib {
    int nhn;
    int f4;
    int maxhn;
    SfxZHn hn[8];
} SfxZLib;

extern SfxZLib sfxz_work;



void sfxzmv_InitLibWork(void);
SfxZHn *sfxzmv_SearchFreeHn(void);
void sfxzmv_InitHn(SfxZHn *zhn);
void sfxzmv_SetTagGrp(SfxZHn *zhn);
void sfxzmv_GetZfrmInf(SfxZHn *zhn, char *tag, char *endtag, char **data, int *size);
void sfxzmv_MakeOrgZ32Tbl(SfxZHn *zhn, int lo, int hi, unsigned int *tbl);
void sfxzmv_MakeCnvZTbl(SfxZHn *zhn, int lo, int hi, unsigned int *buf);
void sfxzmv_MakeZ16TblFromOrgZ32(SfxZHn *zhn, unsigned int *src, short *dst);
void sfxzmv_MakeZ32TblFromOrgZ32(SfxZHn *zhn, unsigned int *src, unsigned int *dst);
int sfxzmv_IsOkZclip(float zmin, float zmax);
void SFXZ_SetZbufType(int value);
int SFXZ_GetZbufType(void);
void sfxcnv_CnvFrmZcmn(SfxHn *hn, SfxFrame *frm, int zbit, int arg);
void sfxcnv_CnvFrmYcc420plnToZ(SfxHn *hn, SfxFrame *frm, int zbit, int arg);
void sfxcnv_CnvFrmArgb8888mbToZ(SfxHn *hn, SfxFrame *frm, int zbit, int arg);
int sfxcnv_CnvZbitToCft(int zbit);

void SFXZ_Init(void) {
    sfxzmv_InitLibWork();
}

void sfxzmv_InitLibWork(void) {
    memset(&sfxz_work, 0, 0x26C);
    sfxz_work.maxhn = 8;
    SFXZ_SetZbufType(0);
}

void SFXZ_Finish(void)
{
}

SfxZHn *SFXZ_Create(void) {
    SfxZHn *zhn = sfxzmv_SearchFreeHn();
    if (zhn == 0) {
        return 0;
    }
    sfxzmv_InitHn(zhn);
    sfxz_work.nhn++;
    zhn->used = 1;
    return zhn;
}

/* matching construct: manual — the in-use word is read through a volatile pointer; retail leaves the loop branch's delay slot empty */
SfxZHn *sfxzmv_SearchFreeHn(void) {
    int maxhn = sfxz_work.maxhn;
    SfxZHn *tbl = sfxz_work.hn;
    volatile SfxZHn *zhn;
    int i;

    for (i = 0; i < maxhn; i++) {
        zhn = &tbl[i];
        if (zhn->used == 0) {
            return (SfxZHn *)zhn;
        }
    }
    return 0;
}

/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void sfxzmv_InitHn(SfxZHn *zhn) {
    zhn->zmin = 0;
    zhn->zmax = 0;
    zhn->cbfn = 0;
    zhn->cbarg = 0;
    zhn->zbit = 0;
}

/* matching construct: manual — the in-use word is written through a volatile pointer; retail leaves the branch delay slot empty */
void SFXZ_Destroy(volatile SfxZHn *zhn) {
    if (zhn != 0) {
        zhn->used = 0;
        sfxz_work.nhn--;
    }
}

void SFXZ_SetTagInf(SfxZHn *zhn, char *data, int size) {
    SfxChunk *info = &zhn->info;
    info->valid = 1;
    info->data = data;
    info->size = size;
    sfxzmv_SetTagGrp(zhn);
}

void sfxzmv_SetTagGrp(SfxZHn *zhn) {
    SfxChunk *hdr = &zhn->hdr;
    SfxChunk *vfrm = &zhn->vfrm;
    SfxChunk *info = &zhn->info;
    SfdSjChunk in;
    SfdSjChunk out;
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
    in.len = info->size;
    SJ_SearchTag(&in, "ZMHDR", "SFXINFE", &out);
    hdr->data = out.data;
    hdr->size = out.len;
    hdr->valid = 1;
    SJ_SearchTag(&in, "ZMVFRM", "SFXINFE", &out);
    vfrm->valid = 1;
    vfrm->data = out.data;
    vfrm->size = out.len;
}

void SFXZ_GetTagInf(SfxZHn *zhn, char **data, int *size) {
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

void SFXZ_GetZfrmRange(SfxZHn *zhn, int frame, int *first, int *second) {
    char *p;
    int len;
    long long n;
    long long x, y, z;
    char *str;
    sfxzmv_GetZfrmInf(zhn, "ZMFSIZE", "SFXINFE", &p, &len);
    if (p == 0) {
        *first = 0;
        *second = 0x7FFFFFFF;
        return;
    }
    sscanf(p, "%lx", &n);
    sfxzmv_GetZfrmInf(zhn, "ZMFDATA", "SFXINFE", &p, &len);
    str = p;
    if (str == 0) {
        *first = 0x7FFFFFFF;
        return;
    }
    sscanf(str + (int)__muldi3(n, frame), "%lx %lx %lx", &x, &y, &z);
    *first = y;
    *second = z;
}

void FUN_002b4630(SfxZHn *zhn, int lo, int hi, unsigned int *tbl) {
    sfxzmv_MakeOrgZ32Tbl(zhn, lo, hi, tbl);
}

void sfxzmv_MakeOrgZ32Tbl(SfxZHn *zhn, int lo, int hi, unsigned int *tbl)
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

void SFXZ_MakeCnvZTbl(SfxZHn *zhn, int frame, unsigned int *buf) {
    int first;
    int second;
    SFXZ_GetZfrmRange(zhn, frame, &first, &second);
    sfxzmv_MakeCnvZTbl(zhn, first, second, buf);
}

void sfxzmv_MakeCnvZTbl(SfxZHn *zhn, int lo, int hi, unsigned int *buf) {
    unsigned int *tbl = buf + 0x100;
    SfxZCbFn cbfn;
    memset(buf, 0, 0x400);
    FUN_002b4630(zhn, lo, hi, tbl);
    cbfn = zhn->cbfn;
    if (cbfn == 0) {
        if (zhn->zbit == 16) {
            sfxzmv_MakeZ16TblFromOrgZ32(zhn, tbl, (short *)buf);
            return;
        }
        sfxzmv_MakeZ32TblFromOrgZ32(zhn, tbl, buf);
        return;
    }
    cbfn(tbl, buf, zhn->zmin, zhn->zmax);
}

void sfxzmv_MakeZ16TblFromOrgZ32(SfxZHn *zhn, unsigned int *src, short *dst) {
    int i;
    if (SFXZ_GetZbufType() == 1) {
        for (i = 0; i < 256; i++) {
            dst[i] = src[i] >> 15;
        }
    } else {
        SFXLIB_Error(0, 0, "E405241: sfxzmv_MakeZ16TblFromOrgZ32() is not support yet.");
    }
}

void sfxzmv_MakeZ32TblFromOrgZ32(SfxZHn *zhn, unsigned int *src, unsigned int *dst)
{
    float scale = zhn->zmax;
    int i;
    unsigned int v;
    if (SFXZ_GetZbufType() == 1) {
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

void SFXZ_SetZclip(SfxZHn *zhn, float zmin, float zmax) {
    if (sfxzmv_IsOkZclip(zmin, zmax) != 1) {
        SFXLIB_Error(0, 0, "E201314: SFXZ_SetZclip : zclip is invalid.");
    }
    zhn->zmin = zmin;
    zhn->zmax = zmax;
}

int sfxzmv_IsOkZclip(float zmin, float zmax) {
    int ok;
    ok = 1;
    if (zmax <= zmin) {
        ok = 0;
    }
    if ((zmax - zmin) < -14.0f) {
        ok = 0;
    }
    return ok;
}

void SFXZ_GetZclip(SfxZHn *zhn, float *zmin, float *zmax) {
    *zmin = zhn->zmin;
    *zmax = zhn->zmax;
}

int SFXZ_IsSetZclip(SfxZHn *zhn) {
    float a = zhn->zmin;
    float b = zhn->zmax;
    int nonzero = 1;
    if (a == 0.0f && b == 0.0f) {
        nonzero = 0;
    }
    return nonzero;
}

void SFXZ_SetZbufType(int value) {
    sfxz_work.f4 = value;
}

int SFXZ_GetZbufType(void) {
    return sfxz_work.f4;
}

void SFX_CnvFrmZ16(SfxHn *hn, SfxFrame *frm, int arg) {
    SFX_SetZbit(hn, 16);
    sfxcnv_CnvFrmZcmn(hn, frm, 16, arg);
}

void SFX_CnvFrmZ24(SfxHn *hn, SfxFrame *frm, int arg) {
    SFX_SetZbit(hn, 24);
    sfxcnv_CnvFrmZcmn(hn, frm, 24, arg);
}

void SFX_CnvFrmZ32(SfxHn *hn, SfxFrame *frm, int arg) {
    SFX_SetZbit(hn, 32);
    sfxcnv_CnvFrmZcmn(hn, frm, 32, arg);
}

void sfxcnv_CnvFrmZcmn(SfxHn *hn, SfxFrame *frm, int zbit, int arg) {
    if (hn->compo == 0) {
        hn->compo = SFXINF_GetStmInf(frm, "COMPO");
    }
    if (SFXZ_IsSetZclip(hn->zhn) != 1) {
        SFXLIB_Error(hn, frm, "E201315: sfxcnv_CnvFrmZcmn : zclip is not set.");
        return;
    }
    switch (frm->frmfmt) {
    case 3:
        sfxcnv_CnvFrmYcc420plnToZ(hn, frm, zbit, arg);
        return;
    case 2:
        sfxcnv_CnvFrmArgb8888mbToZ(hn, frm, zbit, arg);
        return;
    case 1:
    default:
        SFXLIB_Error(hn, frm, "E201191: SFX_CnvFrmZcmn : frmfmt is not support.");
        return;
    }
}

void sfxcnv_CnvFrmYcc420plnToZ(SfxHn *hn, SfxFrame *frm, int zbit, int arg) {
    SfxPlane *py = &frm->plane[0];
    SfxPlane *pu = &frm->plane[1];
    SfxPlane *pv = &frm->plane[2];
    CftYccPln src;
    CftImage dst;
    int pitch;
    int height;
    int ofs;

    src.f24 = 0;
    ofs = py->pitch * py->height / 2;
    src.y = (char *)py->addr + ofs;
    src.u = (char *)pu->addr + ofs / 2;
    src.v = (char *)pv->addr + ofs / 2;
    src.ypitch = py->pitch;
    src.upitch = pu->pitch;
    src.vpitch = pv->pitch;
    if (hn->width == 0)
        pitch = py->pitch;
    else
        pitch = hn->width;
    if (hn->height == 0)
        height = py->height / 2;
    else
        height = hn->height;
    dst.f0 = sfxcnv_CnvZbitToCft(zbit);
    dst.base = (int *)arg;
    dst.stride = pitch;
    dst.f12 = height;
    dst.height = py->pitch;
    dst.width = py->height / 2;
    switch (zbit) {
    case 16:
        SFX_MakeTable(hn, frm, 11);
        CFT_Ycc420plnToZ16(&src, &dst, (int *)hn->tbl[0]);
        break;
    case 32:
        SFX_MakeTable(hn, frm, 13);
        CFT_Ycc420plnToZ32(&src, &dst, (int *)hn->tbl[0]);
        break;
    }
}

int sfxcnv_CnvZbitToCft(int zbit) {
    int r;
    switch ((unsigned int)zbit) {
    case 16: r = 1; break;
    case 24: r = 2; break;
    case 32: r = 3; break;
    case 8:
    default:
        SFXLIB_Error(0, 0, "E201313: sfxcnv_CnvZbitToCft : zbit is invalid.");
        r = 0;
        break;
    }
    return r;
}

/* The pointer must live in v0, so it is returned rather than discarded. */
void *SFX_SetZbit(void *sfx, int zbit) {
    SfxHn *hn = sfx;
    SfxZHn *zhn = hn->zhn;
    zhn->zbit = zbit;
    return zhn;
}

int SFX_GetZbit(SfxHn *hn) {
    return hn->zhn->zbit;
}
