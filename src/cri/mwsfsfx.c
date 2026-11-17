#include "dw4/cri/mwply.h"
#include "dw4/cri/sfx.h"
#include <string.h>
#include "dw4/cri/cri_mwsfd.h"
#include "dw4/cri/sfd.h"
#include "dw4/cri/sj.h"

typedef struct SjObj SjObj;

typedef struct SjChunk {
    char *addr;
    int size;
} SjChunk;

typedef struct SjVtbl {
    void *f0;
    void *f4;
    void *f8;
    void (*destroy)(SjObj *sj);                                   /* 12 */
    void *getUuid;                                                /* 16 */
    void (*reset)(SjObj *sj);                                     /* 20 */
    void (*getChunk)(SjObj *sj, int id, int size, SjChunk *chunk); /* 24 */
    void *ungetChunk;                                             /* 28 */
    void (*putChunk)(SjObj *sj, int id, SjChunk *chunk);          /* 32 */
    int (*getNumData)(SjObj *sj, int id);                         /* 36 */
} SjVtbl;

struct SjObj {
    SjVtbl *vtbl;
};

typedef struct MwsfdFrm {
    int addr;       /* 0 */
    unsigned int bufFmt; /* 4 */
    int width;      /* 8 */
    int height;     /* 12 */
    int f16[8];
    int f48;        /* 48 */
} MwsfdFrm;

extern char DAT_004f4028[];
extern char DAT_004f4050[];
extern char DAT_004f4078[];
extern char DAT_004f40a0[];
extern char DAT_004f40c0[];
extern char DAT_004f40f0[];
extern char DAT_004f4120[];
extern char DAT_004f4150[];
extern char DAT_004f4180[];
extern char DAT_004f41b8[];
extern char DAT_004f4200[];
extern char DAT_004f4250[];
extern char DAT_004f4288[];
extern char DAT_004f42c8[];
extern char DAT_004f4300[];
extern char DAT_004f4338[];
extern char DAT_004f4370[];
extern char DAT_004f43a8[];
extern char DAT_004f43e0[];
extern char CRITAGS[];
extern char CRITAGE[];
extern char DAT_004f4420[];
extern char DAT_004f4458[];
extern char DAT_004f4460[];
extern char DAT_004f4468[];
extern char DAT_004f4498[];
extern char DAT_004f44c8[];
extern char DAT_004f44f8[];
extern char DAT_004f4528[];
extern char DAT_004f4558[];
extern char DAT_004f4588[];
extern char DAT_004f45c0[];

void FUN_002b3b78(void);
void FUN_002b3b88(void);
void FUN_002b3bb8(void *sfx, int value);
void FUN_002b3bf8(void *sfx, int a, int b);
void FUN_002b3c20(void *sfx, int value);
void FUN_002b3dd0(void *sfx, int a, int b, int flag);
void FUN_002b3e00(void *sfx, unsigned char a, unsigned char b, unsigned char c);
void FUN_002b3e58(void *sfx, int value);
void FUN_002b3e60(void *sfx);
void FUN_002b3ff8(void *sfx, int value);
int FUN_002b4050(void *sfx);
void FUN_002b4068(void);
void FUN_002b40b0(void *sfx, char *ud, int size);
void FUN_002b40d0(void *sfx);
int FUN_002b40f0(void *sfx);
int FUN_002b4110(void *sfx);
void FUN_002b4130(void *sfx);
void FUN_002b4150(void *sfx);
void FUN_002b4170(void *sfx);
void FUN_002b4190(void *sfx);
void FUN_002b41b0(void *sfx);
void FUN_002b41d0(void *sfx);
void FUN_002b41f0(void *sfx);
void FUN_002b4ba8(void *sfx, SfxFrame *prm, int arg);
void FUN_002b4c48(void *sfx, SfxFrame *prm, int arg);

void mwsfsfx_SfxErrCbFn(void *ctx, char *msg);
int mwsfsfx_CnvFrmFmtTypeToSfx(unsigned int format);
void mwsfsfx_SetYcc420plnInfToSfx(MwsfdFrm *frm, SfxFrame *prm);
int mwsfsfx_SetNfrm(MwsfdFrm *frm, SfxFrame *prm);
void mwsfsfx_SetSfxBufInf(SfxPlane *plane, int addr, int pitch, int height);
void mwsfsfx_SetSfxInfTag(MwsfdPly *ply, MwsfdFrm *frm, SfxFrame *prm);
void FUN_00297a30(MwsfdPly *ply, SfxFrame *prm);
int FUN_00297aa8(MwsfdPly *ply);
SfxChromaFmt FUN_00297b18(MwsfdPly *ply);
int FUN_00297b88(MwsfdChromaPos position);
void mwPlyFxGetOutBufSize(MwsfdPly *ply, int a, int b, int c);
void mwsfd_GetCriTags(MwsfdPly *ply);
void mwsftag_GetSFXinfFromAinf(MwsfdPly *ply);
int MWSFTAG_ClearUsrSj(MwsfdPly *ply);

void MWSFSFX_Init(void)
{
    SFX_Init();
    SFX_SetErrFn(mwsfsfx_SfxErrCbFn, 0);
}

void mwsfsfx_SfxErrCbFn(void *ctx, char *msg)
{
    MWSFSVM_Error(msg);
}

void MWSFSFX_Finish(void)
{
    SFX_Finish();
}

int MWSFSFX_CalcHnWorkSiz(int width, int height)
{
    return 6175;
}

SfxHn *MWSFSFX_Create(int work, int wksize, int a2, int a3)
{
    return SFX_Create(work, wksize, a2, a3);
}

void MWSFSFX_Destroy(void *sfx)
{
    SFX_Destroy(sfx);
}

void *MWSFSFX_GetSfxHn(MwsfdPly *ply)
{
    return ply->sfx;
}

void MWSFSFX_SetSfxHn(MwsfdPly *ply, void *sfx)
{
    ply->sfx = sfx;
}

void mwsfsfx_CnvFrmInfToSfx(MwsfdPly *ply, MwsfdFrm *frm, SfxFrame *prm);

void MWSFD_CnvFrmInfToSfx(MwsfdPly *ply, MwsfdFrm *frm, SfxFrame *prm)
{
    mwsfsfx_CnvFrmInfToSfx(ply, frm, prm);
}

void mwsfsfx_CnvFrmInfToSfx(MwsfdPly *ply, MwsfdFrm *frm, SfxFrame *prm)
{
    prm->frmfmt = mwsfsfx_CnvFrmFmtTypeToSfx(frm->bufFmt);
    mwsfsfx_SetYcc420plnInfToSfx(frm, prm);
    mwsfsfx_SetNfrm(frm, prm);
    mwsfsfx_SetSfxInfTag(ply, frm, prm);
    FUN_00297a30(ply, prm);
}

int mwsfsfx_CnvFrmFmtTypeToSfx(unsigned int format)
{
    int result;

    switch (format) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        MWSFSVM_Error(DAT_004f4028);
        result = 3;
        break;
    }
    return result;
}

void mwsfsfx_SetYcc420plnInfToSfx(MwsfdFrm *frm, SfxFrame *prm)
{
    int out[6];
    int width = frm->width;
    int height = frm->height;
    int mode = frm->bufFmt;

    prm->width = width;
    prm->height = height;
    if (mode != 3) {
        mwsfsfx_SetSfxBufInf(&prm->plane[0], frm->addr, width, height);
        return;
    }
    mwPlyCalcYccPlane(frm->addr, width, height, out);
    mwsfsfx_SetSfxBufInf(&prm->plane[0], out[0], out[3], height);
    mwsfsfx_SetSfxBufInf(&prm->plane[1], out[1], out[4], height);
    mwsfsfx_SetSfxBufInf(&prm->plane[2], out[2], out[5], height);
}

int mwsfsfx_SetNfrm(MwsfdFrm *frm, SfxFrame *prm)
{
    return prm->fno = frm->f48;
}

void mwsfsfx_SetSfxBufInf(SfxPlane *plane, int addr, int pitch, int height)
{
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    plane->addr = addr;
    plane->pitch = pitch;
    plane->height = height;
}

void mwsfsfx_SetSfxInfTag(MwsfdPly *ply, MwsfdFrm *frm, SfxFrame *prm)
{
    char *data;
    int size;

    SFX_GetTagInf(ply->sfx, &data, &size);
    prm->f80 = (int)data;
    prm->f84 = size;
    prm->f88 = 0;
    prm->f92 = 0;
}

void FUN_00297a30(MwsfdPly *ply, SfxFrame *prm)
{
    SfxPicFmt *dst = &prm->fmt;
    MwsfdPicInf *src;

    dst->pictureStructure = FUN_00297aa8(ply);
    src = &ply->pic;
    dst->chromaFormat = FUN_00297b18(ply);
    dst->f8 = src->f8;
    dst->f12 = src->f12;
    dst->f16 = src->f16;
    dst->chromaPosH = FUN_00297b88(src->chromaPosH);
    dst->chromaPosV = FUN_00297b88(src->chromaPosV);
}

int FUN_00297aa8(MwsfdPly *ply)
{
    int result = 3;

    switch (ply->pic.pictureStructure) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        MWSFSVM_Error(DAT_004f4050);
        break;
    }
    return result;
}

SfxChromaFmt FUN_00297b18(MwsfdPly *ply)
{
    SfxChromaFmt result = SFX_CHROMA_FMT_1;

    switch (ply->pic.chromaFormat) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        MWSFSVM_Error(DAT_004f4078);
        break;
    }
    return result;
}

int FUN_00297b88(MwsfdChromaPos position)
{
    int result = 1;

    switch (position) {
    case 0:
        result = 0;
        break;
    case 1:
        result = 1;
        break;
    default:
        MWSFSVM_Error(DAT_004f40a0);
        break;
    }
    return result;
}

void MWSFD_SetSfxCnvTbl(MwsfdPly *ply, int index, int value)
{
    SFX_SetCnvTable(ply->sfx, index, value);
}

int MWSFD_GetSfxCnvTbl(MwsfdPly *ply, int index)
{
    return SFX_GetCnvTable(ply->sfx, index);
}

void mwPlyFxCnvFrmZ16(MwsfdPly *ply, MwsfdFrm *frm, int arg)
{
    SfxFrame prm;
    void *sfx;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f40c0);
    } else if (frm->addr == 0) {
        MWSFSVM_Error(DAT_004f40f0);
    } else {
        sfx = MWSFSFX_GetSfxHn(ply);
        mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
        FUN_002b4ba8(sfx, &prm, arg);
    }
}

void mwPlyFxCnvFrmZ32(MwsfdPly *ply, MwsfdFrm *frm, int arg)
{
    SfxFrame prm;
    void *sfx;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4120);
    } else if (frm->addr == 0) {
        MWSFSVM_Error(DAT_004f4150);
    } else {
        sfx = MWSFSFX_GetSfxHn(ply);
        mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
        FUN_002b4c48(sfx, &prm, arg);
    }
}

void mwPlyFxSetCompoMode(MwsfdPly *ply, int mode)
{
    int compo = mode;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4180);
        return;
    }
    if (ply->addInfSj == 0) {
        if (mode == 0x101) {
            MWSFSVM_Error(DAT_004f41b8);
            return;
        }
        if (mode == 0) {
            MWSFSVM_Error(DAT_004f4200);
            return;
        }
    }
    compo = mode;
    if (ply->vtbl->getStat(ply) == 2 && compo == 0) {
        compo = mwPlyGetCurPicCompoMode(ply);
        if (compo == -1) {
            compo = 17;
        }
    }
    MWSFSFX_SetCompoMode(ply, compo);
}

void MWSFSFX_SetCompoMode(MwsfdPly *ply, int mode)
{
    SFX_SetCompoMode(MWSFSFX_GetSfxHn(ply), mode);
}

int mwPlyFxGetCompoMode(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4250);
        return 0;
    }
    return SFX_GetCompoMode(MWSFSFX_GetSfxHn(ply));
}

void FUN_00297ee8(MwsfdPly *ply, int value)
{
    SFX_SetOutBufSize(MWSFSFX_GetSfxHn(ply), value);
}

void MWSFSFX_SetColAdj(MwsfdPly *ply, int value)
{
    FUN_002b3e58(ply->sfx, value);
}

void MWSFD_SetColAdj(MwsfdPly *ply, int value)
{
    MWSFSFX_SetColAdj(ply, value);
}

void MWSFD_GetColAdj(MwsfdPly *ply)
{
    FUN_002b3e60(ply->sfx);
}

void FUN_00297f60(MwsfdPly *ply, int a, int b)
{
    mwPlyFxGetOutBufSize(ply, a, b, 0);
}

void mwPlyFxSetOutBufSize(MwsfdPly *ply, int *width, int *height)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4288);
        return;
    }
    SFX_GetOutBufSize(MWSFSFX_GetSfxHn(ply), width, height);
}

void FUN_00297ff8(MwsfdPly *ply, int a, int b)
{
    mwPlyFxGetOutBufSize(ply, a, b, 0);
}

void FUN_00298010(MwsfdPly *ply, int *width, int *height)
{
    mwPlyFxSetOutBufSize(ply, width, height);
}

void mwPlyFxGetOutBufSize(MwsfdPly *ply, int a, int b, int c)
{
    void *sfx;

    if (!MWSFD_IsEnableHndl(ply)) {
        MWSFSVM_Error(DAT_004f42c8);
        return;
    }
    sfx = MWSFSFX_GetSfxHn(ply);
    FUN_002b3bf8(sfx, a, b);
    FUN_002b3c20(sfx, c);
}

void mwPlyFxSetOutZscale(MwsfdPly *ply, int value)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4300);
        return;
    }
    SFX_SetOutZscale(MWSFSFX_GetSfxHn(ply), value);
}

int mwPlyFxGetOutZscale(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4338);
        return 0;
    }
    return SFX_GetOutZscale(MWSFSFX_GetSfxHn(ply));
}

void mwPlyFxSetOutZoffset(MwsfdPly *ply, int value)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4370);
        return;
    }
    SFX_SetOutZoffset(MWSFSFX_GetSfxHn(ply), value);
}

int mwPlyFxGetOutZoffset(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f43a8);
        return 0;
    }
    return SFX_GetOutZoffset(MWSFSFX_GetSfxHn(ply));
}

int mwsftag_IsPlayM1V(MwsfdPly *ply)
{
    return ply->cre.type == 2;
}

int MWSFTAG_IsUseAinfSj(MwsfdCreInf *cre)
{
    int result;

    switch (cre->addInfMode) {
    case 0:
    case 0x101:
        result = 1;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

SjObj *MWSFTAG_CreateAinfSj(MwsfdPly *ply)
{
    SjObj *sj;

    if (MWSFTAG_IsUseAinfSj(&ply->cre) == 0) {
        return 0;
    }
    sj = SJRBF_Create(ply->addInfBase, ply->addInfSize, 0);
    if (sj == 0) {
        MWSFSVM_Error(DAT_004f43e0);
        mwSfdDestroy(ply);
        return 0;
    }
    return sj;
}

void MWSFTAG_DestroyAinfSj(MwsfdPly *ply)
{
    SjObj *sj = ply->addInfSj;

    if (sj != 0) {
        sj->vtbl->destroy(sj);
    }
}

int MWSFTAG_SetAinfSj(MwsfdPly *ply)
{
    SjObj *sj;

    if (mwsftag_IsPlayM1V(ply) == 1) {
        return 0;
    }
    sj = ply->addInfSj;
    if (sj == 0) {
        return 0;
    }
    if (SFD_SetUsrSj(ply->sfd, 2, sj, 0) != 0) {
        return -1;
    }
    return 0;
}

void mwsfsfx_ResetAddInf(MwsfdPly *ply)
{
    MwsfdAddInf *inf = &ply->addInf;

    inf->valid = 0;
    inf->addr = 0;
    inf->size = 0;
    ply->usrBuf.f8 = -1;
}

void MWSFTAG_ResetAinfSj(MwsfdPly *ply)
{
    SjObj *sj = ply->addInfSj;

    if (sj != 0) {
        sj->vtbl->reset(sj);
    }
}

void MWSFTAG_SetTagInf(MwsfdPly *ply)
{
    MwsfdAddInf *inf = &ply->addInf;

    if (ply->addInfSj != 0 && inf->valid != 1) {
        mwsfd_GetCriTags(ply);
        mwsftag_GetSFXinfFromAinf(ply);
    }
}

void mwsfsfx_UpdateAddInf(MwsfdPly *ply)
{
    if (ply->addInfSj == 0) {
        return;
    }
    mwsfd_GetCriTags(ply);
    mwsftag_GetSFXinfFromAinf(ply);
}

void mwsfd_GetCriTags(MwsfdPly *ply)
{
    SjChunk in;
    SjChunk out;
    SjChunk chunk;
    MwsfdAddInf *inf = &ply->addInf;
    SjObj *sj = ply->addInfSj;
    MwsfdUsrBuf *ub;
    int size;

    size = sj->vtbl->getNumData(sj, 1);
    if (size == 0) {
        inf->addr = 0;
        inf->size = 0;
        inf->valid = 1;
        return;
    }
    in.addr = ply->addInfBase;
    in.size = size;
    if (SJ_SearchTag(&in, CRITAGS, CRITAGE, &out) == 0) {
        inf->addr = 0;
        inf->size = 0;
        inf->valid = 1;
        return;
    }
    ub = &ply->usrBuf;
    if (ub->buf != 0) {
        memcpy(ub->buf, out.addr, out.size);
        inf->addr = ub->buf;
        inf->size = out.size;
        inf->valid = 1;
        sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, &chunk);
        sj->vtbl->putChunk(sj, 0, &chunk);
        sj->vtbl->reset(sj);
        return;
    }
    inf->addr = out.addr;
    inf->size = out.size;
    inf->valid = 1;
    MWSFTAG_ClearUsrSj(ply);
}

void mwPlyAttachAddInfBuf(MwsfdPly *ply, char *buf, int size)
{
    MwsfdUsrBuf *ub = &ply->usrBuf;

    if (size < 0x20000) {
        MWSFSVM_Error(DAT_004f4420);
    }
    ub->buf = buf;
    ub->size = size;
}

void mwsftag_GetSFXinfFromAinf(MwsfdPly *ply)
{
    SjChunk in;
    SjChunk out;
    MwsfdAddInf *inf = &ply->addInf;
    void *sfx = ply->sfx;

    if (inf->addr == 0) {
        SFX_SetTagInf(sfx, 0, 0);
        return;
    }
    in.addr = inf->addr;
    in.size = inf->size;
    if (SJ_SearchTag(&in, DAT_004f4458, DAT_004f4460, &out) == 0) {
        SFX_SetTagInf(sfx, 0, 0);
        return;
    }
    SFX_SetTagInf(sfx, out.addr, out.size);
}

int MWSFTAG_ClearUsrSj(MwsfdPly *ply)
{
    if (mwsftag_IsPlayM1V(ply) == 1) {
        return 0;
    }
    if (ply->addInfSj == 0) {
        return 0;
    }
    if (SFD_SetUsrSj(ply->sfd, 2, 0, 0) != 0) {
        return -1;
    }
    return 0;
}

void mwPlyFxSetZclip(MwsfdPly *ply, float zmin, float zmax)
{
    SFX_SetZclip(ply->sfx, zmin, zmax);
}

void mwPlyFxGetZclip(MwsfdPly *ply, float *zmin, float *zmax)
{
    SFX_GetZclip(ply->sfx, zmin, zmax);
}

void MWSFD_GetAinfAll(MwsfdPly *ply, char **addr, int *size)
{
    MwsfdAddInf *inf = &ply->addInf;

    *addr = inf->addr;
    *size = inf->size;
}

void MWSFD_GetAinfFx(MwsfdPly *ply, char **data, int *size)
{
    SjChunk zinf;

    SFX_GetTagInf(ply->sfx, &zinf.addr, &zinf.size);
    *data = zinf.addr;
    *size = zinf.size;
}

void MWSFD_GetZfrmRange(MwsfdPly *ply, MwsfdFrm *frm, int *first, int *second)
{
    SfxFrame prm;
    void *sfx = MWSFSFX_GetSfxHn(ply);

    mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
    SFX_GetZfrmRange(sfx, &prm, first, second);
}

void mwPlyFxSetLumiPrm(MwsfdPly *ply, int a, int b, int mode)
{
    FUN_002b3dd0(MWSFSFX_GetSfxHn(ply), a, b, mode == 1);
}

/* The luminance-key parameters of the sfx; the key comes back as an MwsfdLumiKey, an enum, so its
 * store does not alias the int stores and retail's store order holds. */
void mwPlyFxGetLumiPrm(MwsfdPly *ply, int *first, int *second, MwsfdLumiKey *flag)
{
    int a;
    int b;
    int c;
    int s;
    MwsfdLumiKey fl;

    SFX_SetALumiPrm(MWSFSFX_GetSfxHn(ply), &a, &b, &c);
    s = b;
    fl = (c ^ 1) != 0 ? 0 : c;
    *first = a;
    *flag = fl;
    *second = s;
}

void FUN_002988f0(MwsfdPly *ply, unsigned char a, unsigned char b, unsigned char c)
{
    FUN_002b3e00(MWSFSFX_GetSfxHn(ply), a, b, c);
}

void FUN_00298940(MwsfdPly *ply, unsigned char *a, unsigned char *b, unsigned char *c)
{
    SFX_GetALumiPrm(MWSFSFX_GetSfxHn(ply), a, b, c);
}

void MWSFD_MakeTblZ16(MwsfdPly *ply, MwsfdFrm *frm)
{
    SfxFrame prm;
    void *sfx;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4468);
        return;
    }
    if (frm->addr == 0) {
        MWSFSVM_Error(DAT_004f4498);
        return;
    }
    sfx = MWSFSFX_GetSfxHn(ply);
    mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
    SFX_MakeTblZ16(sfx, &prm);
}

void MWSFD_MakeTblZ32(MwsfdPly *ply, MwsfdFrm *frm)
{
    SfxFrame prm;
    void *sfx;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f44c8);
        return;
    }
    if (frm->addr == 0) {
        MWSFSVM_Error(DAT_004f44f8);
        return;
    }
    sfx = MWSFSFX_GetSfxHn(ply);
    mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
    SFX_MakeTblZ32(sfx, &prm);
}

void mwsfsfx_SetPicUsr(MwsfdPly *ply, char *ud, int size)
{
    FUN_002b40b0(ply->sfx, ud, size);
}

int MWSFSFX_SetPicUsrDat(MwsfdPly *ply)
{
    return FUN_002b4110(ply->sfx);
}

void MWSFSFX_IsFrmCcs(MwsfdPly *ply)
{
    FUN_002b40d0(ply->sfx);
}

int MWSFD_IsFrmDivField(MwsfdPly *ply)
{
    return FUN_002b40f0(ply->sfx);
}

void MWSFD_IsFrmCcs(MwsfdPly *ply)
{
    MWSFSFX_SetPicUsrDat(ply);
}

void FUN_00298b48(MwsfdPly *ply)
{
    FUN_002b4130(ply->sfx);
}

void FUN_00298b60(MwsfdPly *ply)
{
    FUN_002b4150(ply->sfx);
}

void FUN_00298b78(MwsfdPly *ply)
{
    FUN_002b4170(ply->sfx);
}

void FUN_00298b90(MwsfdPly *ply)
{
    FUN_002b4190(ply->sfx);
}

void FUN_00298ba8(MwsfdPly *ply)
{
    FUN_002b41b0(ply->sfx);
}

void FUN_00298bc0(MwsfdPly *ply)
{
    FUN_002b41d0(ply->sfx);
}

void FUN_00298bd8(MwsfdPly *ply)
{
    FUN_002b41f0(ply->sfx);
}

void MWSFD_SetSplitField(MwsfdPly *ply, int value)
{
    SFX_SetColAdj(ply->sfx, value);
}

int MWSFD_GetSplitField(MwsfdPly *ply)
{
    return SFX_GetColAdj(ply->sfx);
}

void MWSFD_SetProgOut(MwsfdPly *ply, int value)
{
    SFX_SetSplitField(ply->sfx, value);
}

int MWSFD_GetProgOut(MwsfdPly *ply)
{
    return SFX_GetSplitField(ply->sfx);
}

void FUN_00298c50(void)
{
    FUN_002b3b78();
}

void FUN_00298c68(void)
{
    FUN_002b3b88();
}

void FUN_00298c80(MwsfdPly *ply, int value)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4528);
        return;
    }
    FUN_002b3ff8(MWSFSFX_GetSfxHn(ply), value);
}

int FUN_00298ce8(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4558);
        return 0;
    }
    return FUN_002b4050(MWSFSFX_GetSfxHn(ply));
}

void FUN_00298d48(MwsfdPly *ply, int value)
{
    FUN_002b3bb8(MWSFSFX_GetSfxHn(ply), value);
}

void mwsfsfx_SetCompoMode(MwsfdPly *ply)
{
    int mode;

    if (ply->compoSet == 0) {
        mode = mwPlyGetCurPicCompoMode(ply);
        if (mode != -1) {
            ply->compoMode = mode;
        } else {
            ply->compoMode = 0x11;
        }
    }
    SFX_SetCompoMode(MWSFSFX_GetSfxHn(ply), ply->compoMode);
}

void mwPlySetCnvBottomUp(MwsfdPly *ply, int value)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f4588);
        return;
    }
    SFX_SetProgOut(MWSFSFX_GetSfxHn(ply), value);
}

int mwPlyGetCnvBottomUp(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error(DAT_004f45c0);
        return 0;
    }
    return SFX_GetProgOut(MWSFSFX_GetSfxHn(ply));
}

void FUN_00298ea8(void)
{
    FUN_002b4068();
}
