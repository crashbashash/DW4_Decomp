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


void FUN_002b3bb8(void *sfx, int value);
void FUN_002b4068(void);
void FUN_002b4130(void *sfx);
void FUN_002b4150(void *sfx);
void FUN_002b4170(void *sfx);
void FUN_002b4190(void *sfx);
void FUN_002b41b0(void *sfx);
void FUN_002b41d0(void *sfx);
void FUN_002b41f0(void *sfx);

void mwsfsfx_SfxErrCbFn(void *ctx, char *msg);
int mwsfsfx_CnvFrmFmtTypeToSfx(unsigned int format);
void mwsfsfx_SetYcc420plnInfToSfx(MwsfdFrm *frm, SfxFrame *prm);
int mwsfsfx_SetNfrm(MwsfdFrm *frm, SfxFrame *prm);
void mwsfsfx_SetSfxBufInf(SfxPlane *plane, int addr, int pitch, int height);
void mwsfsfx_SetSfxInfTag(MwsfdPly *ply, MwsfdFrm *frm, SfxFrame *prm);
void mwsfsfx_SetPicFmtToSfx(MwsfdPly *ply, SfxFrame *prm);
int mwsfsfx_CnvPicStructToSfx(MwsfdPly *ply);
SfxChromaFmt mwsfsfx_CnvChromaFmtToSfx(MwsfdPly *ply);
int mwsfsfx_CnvChromaPosToSfx(MwsfdChromaPos position);
void MWSFSFX_SetOutBufSize(MwsfdPly *ply, int a, int b, int c);
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
    mwsfsfx_SetPicFmtToSfx(ply, prm);
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
        MWSFSVM_Error("E201184 : MwsfdBufFmt value is invalid.");
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

void mwsfsfx_SetPicFmtToSfx(MwsfdPly *ply, SfxFrame *prm)
{
    SfxPicFmt *dst = &prm->fmt;
    MwsfdPicInf *src;

    dst->pictureStructure = mwsfsfx_CnvPicStructToSfx(ply);
    src = &ply->pic;
    dst->chromaFormat = mwsfsfx_CnvChromaFmtToSfx(ply);
    dst->f8 = src->f8;
    dst->f12 = src->f12;
    dst->f16 = src->f16;
    dst->chromaPosH = mwsfsfx_CnvChromaPosToSfx(src->chromaPosH);
    dst->chromaPosV = mwsfsfx_CnvChromaPosToSfx(src->chromaPosV);
}

int mwsfsfx_CnvPicStructToSfx(MwsfdPly *ply)
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
        MWSFSVM_Error("E301272 : picture_structure is invalid.");
        break;
    }
    return result;
}

SfxChromaFmt mwsfsfx_CnvChromaFmtToSfx(MwsfdPly *ply)
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
        MWSFSVM_Error("E301273 : chroma_format is invalid.");
        break;
    }
    return result;
}

int mwsfsfx_CnvChromaPosToSfx(MwsfdChromaPos position)
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
        MWSFSVM_Error("E301274 : chromapos is invalid.");
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
        MWSFSVM_Error("E2011911: mwPlyFxCnvFrmZ16: handle is invalid.");
    } else if (frm->addr == 0) {
        MWSFSVM_Error("E2011912: mwPlyFxCnvFrmZ16: getfrm is failed.");
    } else {
        sfx = MWSFSFX_GetSfxHn(ply);
        mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
        SFX_CnvFrmZ16(sfx, &prm, arg);
    }
}

void mwPlyFxCnvFrmZ32(MwsfdPly *ply, MwsfdFrm *frm, int arg)
{
    SfxFrame prm;
    void *sfx;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E2011913: mwPlyFxCnvFrmZ32: handle is invalid.");
    } else if (frm->addr == 0) {
        MWSFSVM_Error("E2011914: mwPlyFxCnvFrmZ32: getfrm is failed.");
    } else {
        sfx = MWSFSFX_GetSfxHn(ply);
        mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
        SFX_CnvFrmZ32(sfx, &prm, arg);
    }
}

void mwPlyFxSetCompoMode(MwsfdPly *ply, int mode)
{
    int compo = mode;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E201214: mwPlyFxSetCompoMode: handle is invalid.");
        return;
    }
    if (ply->addInfSj == 0) {
        if (mode == 0x101) {
            MWSFSVM_Error("E204011: mwPlyFxSetCompoMode: COMPO_Z needs setting in MWPLY Creation.");
            return;
        }
        if (mode == 0) {
            MWSFSVM_Error("E204012: mwPlyFxSetCompoMode: COMPO_AUTO needs setting in MWPLY Creation.");
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
        MWSFSVM_Error("E2011915: mwPlyFxGetCompoMode: handle is invalid.");
        return 0;
    }
    return SFX_GetCompoMode(MWSFSFX_GetSfxHn(ply));
}

void MWSFSFX_SetFxType(MwsfdPly *ply, int value)
{
    SFX_SetFxType(MWSFSFX_GetSfxHn(ply), value);
}

void MWSFSFX_SetColAdj(MwsfdPly *ply, int value)
{
    SFX_SetColAdj(ply->sfx, value);
}

void MWSFD_SetColAdj(MwsfdPly *ply, int value)
{
    MWSFSFX_SetColAdj(ply, value);
}

void MWSFD_GetColAdj(MwsfdPly *ply)
{
    SFX_GetColAdj(ply->sfx);
}

void mwPlyFxSetOutBufPitchHeight(MwsfdPly *ply, int a, int b)
{
    MWSFSFX_SetOutBufSize(ply, a, b, 0);
}

void mwPlyFxGetOutBufPitchHeight(MwsfdPly *ply, int *width, int *height)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E307092: mwPlyFxGetOutBufPitchHeight: handle is invalid.");
        return;
    }
    SFX_GetOutBufSize(MWSFSFX_GetSfxHn(ply), width, height);
}

void mwPlyFxSetOutBufSize(MwsfdPly *ply, int a, int b)
{
    MWSFSFX_SetOutBufSize(ply, a, b, 0);
}

void mwPlyFxGetOutBufSize(MwsfdPly *ply, int *width, int *height)
{
    mwPlyFxGetOutBufPitchHeight(ply, width, height);
}

void MWSFSFX_SetOutBufSize(MwsfdPly *ply, int a, int b, int c)
{
    void *sfx;

    if (!MWSFD_IsEnableHndl(ply)) {
        MWSFSVM_Error("E306091: MWSFSFX_SetOutBufSize: handle is invalid.");
        return;
    }
    sfx = MWSFSFX_GetSfxHn(ply);
    SFX_SetOutBufSize(sfx, a, b);
    SFX_SetUnitWidth(sfx, c);
}

void mwPlyFxSetOutZscale(MwsfdPly *ply, int value)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E2011918: mwPlyFxSetOutZscale: handle is invalid.");
        return;
    }
    SFX_SetOutZscale(MWSFSFX_GetSfxHn(ply), value);
}

int mwPlyFxGetOutZscale(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E2011919: mwPlyFxGetOutZscale: handle is invalid.");
        return 0;
    }
    return SFX_GetOutZscale(MWSFSFX_GetSfxHn(ply));
}

void mwPlyFxSetOutZoffset(MwsfdPly *ply, int value)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E2011920: mwPlyFxSetOutZoffset: handle is invalid.");
        return;
    }
    SFX_SetOutZoffset(MWSFSFX_GetSfxHn(ply), value);
}

int mwPlyFxGetOutZoffset(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E2011921: mwPlyFxGetOutZoffset: handle is invalid.");
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
        MWSFSVM_Error("E201211 mwPlyCreate: can't create AddInfSJ");
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
    if (SJ_SearchTag(&in, "CRITAGS", "CRITAGE", &out) == 0) {
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
        MWSFSVM_Error("W2121001 : mwPlyAttachAddInfBuf(): bufsize is short.");
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
    if (SJ_SearchTag(&in, "SFXINFS", "SFXINFE", &out) == 0) {
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
    SFX_SetALumiPrm(MWSFSFX_GetSfxHn(ply), a, b, mode == 1);
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

    SFX_GetALumiPrm(MWSFSFX_GetSfxHn(ply), &a, &b, &c);
    s = b;
    fl = (c ^ 1) != 0 ? 0 : c;
    *first = a;
    *flag = fl;
    *second = s;
}

void mwPlyFxSetAlp3Prm(MwsfdPly *ply, unsigned char a, unsigned char b, unsigned char c)
{
    SFX_SetAlp3Prm(MWSFSFX_GetSfxHn(ply), a, b, c);
}

void mwPlyFxGetAlp3Prm(MwsfdPly *ply, unsigned char *a, unsigned char *b, unsigned char *c)
{
    SFX_GetAlp3Prm(MWSFSFX_GetSfxHn(ply), a, b, c);
}

void MWSFD_MakeTblZ16(MwsfdPly *ply, MwsfdFrm *frm)
{
    SfxFrame prm;
    void *sfx;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E202283: MWSFD_MakeTblZ16: handle is invalid.");
        return;
    }
    if (frm->addr == 0) {
        MWSFSVM_Error("E202284: MWSFD_MakeTblZ16: getfrm is failed.");
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
        MWSFSVM_Error("E202285: MWSFD_MakeTblZ32: handle is invalid.");
        return;
    }
    if (frm->addr == 0) {
        MWSFSVM_Error("E202286: MWSFD_MakeTblZ32: getfrm is failed.");
        return;
    }
    sfx = MWSFSFX_GetSfxHn(ply);
    mwsfsfx_CnvFrmInfToSfx(ply, frm, &prm);
    SFX_MakeTblZ32(sfx, &prm);
}

void MWSFSFX_SetPicUsrDat(MwsfdPly *ply, char *ud, int size)
{
    SFX_SetPicUsrDat(ply->sfx, ud, size);
}

int MWSFSFX_IsFrmCcs(MwsfdPly *ply)
{
    return SFX_GetTypeCcs(ply->sfx);
}

void MWSFSFX_GetSudVersion(MwsfdPly *ply)
{
    SFX_GetSudVersion(ply->sfx);
}

int MWSFD_IsFrmDivField(MwsfdPly *ply)
{
    return SFX_GetTypeDivField(ply->sfx);
}

void MWSFD_IsFrmCcs(MwsfdPly *ply)
{
    MWSFSFX_IsFrmCcs(ply);
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
    SFX_SetSplitField(ply->sfx, value);
}

int MWSFD_GetSplitField(MwsfdPly *ply)
{
    return SFX_GetSplitField(ply->sfx);
}

void MWSFD_SetProgOut(MwsfdPly *ply, int value)
{
    SFX_SetProgOut(ply->sfx, value);
}

int MWSFD_GetProgOut(MwsfdPly *ply)
{
    return SFX_GetProgOut(ply->sfx);
}

void MWSFD_SetCcirFx(int value)
{
    SFX_SetCcirFx(value);
}

int MWSFD_GetCcirFx(void)
{
    return SFX_GetCcirFx();
}

void MWSFD_SetMaxAlpha(MwsfdPly *ply, int value)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E304162: MWSFD_GetMaxAlpha: handle is invalid.");
        return;
    }
    SFX_SetMaxAlpha(MWSFSFX_GetSfxHn(ply), value);
}

int MWSFD_GetMaxAlpha(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E304161: MWSFD_GetMaxAlpha: handle is invalid.");
        return 0;
    }
    return SFX_GetMaxAlpha(MWSFSFX_GetSfxHn(ply));
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
        MWSFSVM_Error("E404010: mwPlySetCnvBottomUp: handle is invalid.");
        return;
    }
    SFX_SetCnvBottomUp(MWSFSFX_GetSfxHn(ply), value);
}

int mwPlyGetCnvBottomUp(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E404011: mwPlyGetCnvBottomUp: handle is invalid.");
        return 0;
    }
    return SFX_GetCnvBottomUp(MWSFSFX_GetSfxHn(ply));
}

void FUN_00298ea8(void)
{
    FUN_002b4068();
}
