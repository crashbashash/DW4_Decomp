#include "dw4/cri/sfx.h"
#include <stdio.h>
#include <string.h>
#include "dw4/cri/sj.h"
#include "dw4/support/softfloat.h"

typedef struct SfxZLib {
    int nhn;
    int zbufType;   /* SFXZ_SetZbufType: 1 builds the tables straight from the 32-bit Z */
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
CftZFmt sfxcnv_CnvZbitToCft(int zbit);

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

/* sfxzmv_GetZfrmInf: the Z-frame chunk's `tag` .. `endtag` entry, or 0 and 0 when there is no chunk.
 * Its plain C, which the 2002 SDK's sfx_zmv.o is compiled from word for word:
 *
 *     void sfxzmv_GetZfrmInf(SfxZHn *zhn, char *tag, char *endtag, char **data, int *size) {
 *         SfxChunk *vfrm = &zhn->vfrm;
 *         SfdSjChunk in;
 *         SfdSjChunk out;
 *         if (vfrm->valid != 1 || vfrm->data == 0) {
 *             *data = 0;
 *             *size = 0;
 *             return;
 *         }
 *         in.data = vfrm->data;
 *         in.len = vfrm->size;
 *         SJ_SearchTag(&in, tag, endtag, &out);
 *         *data = out.data;
 *         *size = out.len;
 *     }
 *
 * Under this unit's ee-gcc 2.96 it is the SDK object's code: the copy of `size` fills the first
 * test's branch delay slot (`bne; move s1,t0`). This build was made by a later tool chain: the copy
 * stays before `sd ra`, the slot takes the target's first store (`bnel; sw zero,0(s0)`), the branch
 * skips that store, and the label after the failure path's `b` is padded to 8 bytes with a `nop`
 * nothing reaches. No C spelling gives that under 2.96, so the function is written as assembly. */
__asm__(
    "\t.section .text.sfxzmv_GetZfrmInf,\"ax\",@progbits\n"
    "\t.align 3\n"
    "\t.globl sfxzmv_GetZfrmInf\n"
    "\t.ent sfxzmv_GetZfrmInf\n"
    "sfxzmv_GetZfrmInf:\n"
    "\t.frame $sp, 64, $31\n"
    "\t.mask 0x80030000, -16\n"
    "\t.set noreorder\n"
    "\taddiu $sp, $sp, -64\n"
    "\taddiu $4, $4, 40\n"             /* a0: vfrm = &zhn->vfrm */
    "\tsd $16, 32($sp)\n"
    "\tmove $16, $7\n"                 /* s0: data */
    "\tsd $17, 40($sp)\n"
    "\tmove $17, $8\n"                 /* s1: size */
    "\tsd $31, 48($sp)\n"
    "\tli $3, 1\n"
    "\tlw $2, 0($4)\n"                 /* vfrm->valid */
    "\tbnel $2, $3, .Lno_chunk\n"
    "\tsw $0, 0($16)\n"                /* *data = 0 */
    "\tlw $3, 4($4)\n"                 /* vfrm->data */
    "\tbnel $3, $0, .Lsearch\n"
    "\tlw $2, 8($4)\n"                 /* vfrm->size */
    "\tsw $0, 0($16)\n"                /* *data = 0 */
    ".Lno_chunk:\n"
    "\tb .Ldone\n"
    "\tsw $0, 0($17)\n"                /* *size = 0 */
    "\tnop\n"
    ".Lsearch:\n"
    "\tmove $4, $sp\n"                 /* &in */
    "\taddiu $7, $sp, 16\n"            /* &out */
    "\tsw $3, 0($sp)\n"                /* in.data */
    "\tjal SJ_SearchTag\n"
    "\tsw $2, 4($sp)\n"                /* in.len */
    "\tlw $3, 16($sp)\n"
    "\tlw $2, 20($sp)\n"
    "\tsw $3, 0($16)\n"                /* *data = out.data */
    "\tsw $2, 0($17)\n"                /* *size = out.len */
    ".Ldone:\n"
    "\tld $16, 32($sp)\n"
    "\tld $17, 40($sp)\n"
    "\tld $31, 48($sp)\n"
    "\tjr $31\n"
    "\taddiu $sp, $sp, 64\n"
    "\t.set reorder\n"
    "\t.end sfxzmv_GetZfrmInf\n"
    "\t.previous\n");

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

void sfxzmv_MakeOrgZTbl(SfxZHn *zhn, int lo, int hi, unsigned int *tbl) {
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
    sfxzmv_MakeOrgZTbl(zhn, lo, hi, tbl);
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
    sfxz_work.zbufType = value;
}

int SFXZ_GetZbufType(void) {
    return sfxz_work.zbufType;
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

    src.rsv = 0;
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
    dst.zfmt = sfxcnv_CnvZbitToCft(zbit);
    dst.base = (int *)arg;
    dst.stride = pitch;
    dst.lines = height;
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

void sfxcnv_CnvFrmArgb8888mbToZ(SfxHn *hn, SfxFrame *frm, int zbit, int arg) {
    SfxPlane *pln = &frm->plane[0];
    int width = hn->width;
    int height = hn->height;
    CftArgb8888mb src;
    CftImage dst;
    int pitch;
    int lines;

    src.addr = pln->addr;
    src.pitch = pln->pitch;
    src.height = pln->height;
    src.mbPitch = 64;
    if (width == 0)
        pitch = pln->pitch;
    else
        pitch = width;
    if (height == 0)
        lines = pln->height / 2;
    else
        lines = height;
    dst.zfmt = sfxcnv_CnvZbitToCft(zbit);
    dst.base = (int *)arg;
    dst.stride = pitch;
    dst.lines = lines;
    dst.height = pln->pitch;
    dst.width = pln->height / 2;
    switch (zbit) {
    case 16:
        break;
    case 32:
        SFX_MakeTable(hn, frm, 13);
        CFT_Argb8888mbToZ32((unsigned char **)&src, &dst, (int *)hn->tbl[0]);
        break;
    }
}

CftZFmt sfxcnv_CnvZbitToCft(int zbit) {
    CftZFmt r;
    switch ((unsigned int)zbit) {
    case 16: r = CFT_ZFMT_Z16; break;
    case 24: r = CFT_ZFMT_Z24; break;
    case 32: r = CFT_ZFMT_Z32; break;
    case 8:
    default:
        SFXLIB_Error(0, 0, "E201313: sfxcnv_CnvZbitToCft : zbit is invalid.");
        r = CFT_ZFMT_NONE;
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
