/* CRI MWSFD player creation (MWSFCRE): work-area sizes, the frame and picture user buffers, the SFD
 * handle set-up and teardown, mwPlyGetHdrInf and the player's work-area allocator (MWSFD_Malloc). */
#include "dw4/cri/cri_mwsfd.h"
#include "dw4/cri/sj.h"
#include <string.h>
#include "dw4/cri/sfd.h"
#include "dw4/cri/lsc.h"
#include "dw4/cri/sfmpv.h"

#define MWSFD_MALLOC_MAX 32
#define MWSFD_ADDINF_BUF_SIZE 0x20000

/* the two buffers a player decodes into */
typedef struct MwsfdFrmBufs {
    void *frm;  /* the frame pool: width * height * 9 / 2 + 10304 bytes */
    void *dec;  /* the decoder's fixed work */
} MwsfdFrmBufs;

extern int mwsfd_option;
extern int mpv_frm_buf_num;     /* caller frame buffers (0: allocate per player) */
extern int mpv_frm_buf_size;
extern void *mpv_frm_buf_table[];
extern MwsfdPlyVtbl mwply_vtbl;

extern char E206011_MwsfdCrePrm_illigal_buffmt[];
extern char E1122613_mwPlyCalcWorkCprmSfd_cprm_is_NULL[];
extern char E02120501_Internal_Error_mwsfcre_AttachPicUsrBuf[];
extern char E02120502_mwsfcre_AttachPicUsrBuf_usrdatbuf_is_short[];
extern char mwPlyAttachPicUsrBuf_short_msg[];
extern char E20010703B_MWSFCRE_SetSupplySj[];
extern char E20010703E_MWSFCRE_DestroySfd[];
extern char E0203261_MWSFCRE_ResetSfdHn_SFD_Stop_failed[];
extern char E0203262_MWSFCRE_ResetSfdHn_SFD_SetErrFn_failed[];
extern char E3012100_M1V_Decode_is_not_support_yet[];
extern char E3012101_Buffer_format_is_invalid[];
extern char E2053003_not_enough_work_sfx_wk[];
extern char E2053004_not_enough_work_ainfsj_buf[];
extern char E2053005_forgot_free[];
extern char E204161_mwPlyGetHdrInf_NULL_pointer[];
extern char E204162_mwPlyGetHdrInf_bufsize_error[];
extern char E2053001_MWSFD_Malloc_cnt_over[];
extern char E2053002_not_enough_work[];
extern char E4041301_not_enough_work[];
extern char E20010703C_mwPlyCreateSofdec_create_error[];
extern char E20010703D_mwPlyCreateSofdec_set_errcb[];

/* what an SFD's input SJ is laid over */
typedef enum SfdSupplyKind {
    SFD_SUPPLY_INPUT_RING = 0,    /* the player's input ring */
    SFD_SUPPLY_MEM = 1,           /* a memory buffer */
    SFD_SUPPLY_USR = 2            /* a caller's SJ */
} SfdSupplyKind;

/* where SFD reads its input from (SFD_SetSupplySj's argument); the buffer is passed as an address */
typedef struct SfdSupplyPrm {
    SfdSupplyKind kind;
    SfdSj *sj;
    unsigned int buf;
    int size;
    int xsize;
    int f20;
} SfdSupplyPrm;

/* the buffer sizes mwsfcre_CreateSfd works out for the player being made */
extern unsigned int mwsfd_sisjadr; /* the input ring's start, aligned to 64 bytes */
extern int sjb;                    /* the input ring (the file SJ) */
extern int sib;                    /* the system stream input */
extern int vib;                    /* the video stream input */
extern int aib;                    /* the audio stream input */
extern int rfb;                    /* the reference frames */
extern int tab;                    /* the decoded frames */
extern int adxwk;                  /* the ADXT work */
extern int adxibuf;                /* the ADXT input ring */
/* the creation parameters of each file type: video and audio, video only (MPEG), video only (SFD) */
extern SfdCrePrm mwsfd_sfdmps_crepara;
extern SfdCrePrm mwsfd_sfdmpv_crepara;
extern SfdCrePrm mwsfd_vonlysfd_crepara;
extern SfdMpvCond mwsfd_mpvpara;
extern SfdAdxCfg mwsfd_adxtpara;

void *mwsfcre_CreateSfd(MwsfdPly *ply, MwsfdCreInf *cprm);
int mwsfcre_IsOutFmtDirect(unsigned int format);
void mwPlySetSysPicUsrBuf(MwsfdPly *ply, char *buf, int bufsize, int offset);
int mwsfcre_CheckCprm(MwsfdCreInf *cprm);
int mwsfcre_IsOkUsrMalloc(MwsfdCreInf *cprm);
void mwsfcre_InitMemMng(MwsfdPly *ply, MwsfdCreInf *cprm);
int mwsfcre_MallocCompoWork(MwsfdPly *ply);
int mwsfcre_ConvBufFmtFromMwsfd(int format);


int mwPlyCalcWorkSfd(MwsfdCreInf *cprm);
int mwPlyCalcWorkCompo(MwsfdCreInf *cprm);
void *MWSFD_Malloc(MwsfdPly *ply, int size);
void *mwsfcre_OrgMalloc(MwsfdPly *ply, int size);
void *mwsfcre_UsrMalloc(int size);
int mwsfcre_IncMallocCnt(MwsfdPly *ply);
int mwsfcre_DecMallocCnt(MwsfdPly *ply);
int mwsfcre_GetMallocCnt(MwsfdPly *ply);
void mwsfcre_OrgFree(MwsfdPly *ply, void *ptr);
void mwsfcre_UsrFree(void *ptr);
void mwsfcre_AllFree(MwsfdPly *ply);
int mwsfcre_DecideFtypeByHdrInf(SfdAnaInf *inf);
int mwsfdcre_IsPlayableByHdrInf(MwsfdHdrInf *hdr);

/* matching construct: permuter, reduced by hand: the type read in each test */
void mwsfcre_CalcWorkStmBuf(MwsfdCreInf *cprm, int *inBuf, int *f1, int *xBuf, int *mpv0, int *mpv1,
                              int *mpv2) {
    int nfrm = cprm->nfrm;
    int maxBps;

    if (nfrm <= 0)
        nfrm = 1;
    maxBps = cprm->maxBps;
    if (cprm->type == 2) {
        *inBuf = maxBps / 16384 * nfrm * 2048;
        *f1 = 0;
        *xBuf = 0;
        *mpv0 = 0;
        *mpv1 = 0;
        *mpv2 = 0;
    } else if (cprm->type == 3) {
        *inBuf = maxBps / 16384 * nfrm * 2048;
        *f1 = 0;
        *xBuf = maxBps / 16384 * 1024 + 2048;
        *mpv0 = 0;
        *mpv1 = 0;
        *mpv2 = 0;
    } else {
        *inBuf = maxBps / 16384 * nfrm * 2048;
        *f1 = 0;
        *xBuf = maxBps / 16384 * 1024 + 2048;
        *mpv0 = 24012;
        *mpv1 = 24332;
        *mpv2 = 33216;
    }
}

/* the picture size, and the chroma plane's: half the width rounded up to 32, half the height */
void mwsfcre_CalcFrmRes(MwsfdCreInf *cprm, int *width, int *height, int *halfWidth, int *halfHeight) {
    int w = cprm->maxWidth;
    int h = cprm->maxHeight;

    *halfWidth = (w / 2 + 31) / 32 * 32;
    *halfHeight = h / 2;
    *width = w;
    *height = h;
}

/* the decoder's frame pool, and the picture buffers of nfrmPoolWk frames; both 0 when the caller supplies buffers */
void mwsfcre_CalcWorkFrmBuf(MwsfdCreInf *cprm, int *frmSize, int *picBufSize) {
    int width;
    int height;
    int halfWidth;
    int halfHeight;
    int nfrm;
    int fmt;
    int mbWidth;
    int mbHeight;
    int size;

    if (mpv_frm_buf_num != 0) {
        *frmSize = 0;
        *picBufSize = 0;
        return;
    }
    nfrm = cprm->nfrmPoolWk;
    mwsfcre_CalcFrmRes(cprm, &width, &height, &halfWidth, &halfHeight);
    fmt = mwsfcre_ConvBufFmtFromMwsfd(cprm->bufFmt);
    *frmSize = width * height * 9 / 2 + 551184;
    mbWidth = width / 16;
    mbHeight = height / 16;
    if (fmt == 2) {
        size = nfrm * (mbWidth * mbHeight * 1024 + 64);
    } else {
        size = nfrm * (mbWidth * mbHeight * 384 + 64);
    }
    *picBufSize = size;
}

/* the internal buffer format of a creation parameter's one */
int mwsfcre_ConvBufFmtFromMwsfd(int format) {
    int result;

    if (format == 1) {
        result = 1;
    } else if (format == 0) {
        result = 2;
    } else if (format == 2) {
        result = 2;
    } else if (format == 3) {
        result = 3;
    } else {
        MWSFSVM_Error(E206011_MwsfdCrePrm_illigal_buffmt);
        result = 3;
    }
    return result;
}

/* The stores go through a statement macro (do/while(0)); its loop notes keep sched1/sched2 from hoisting
 * the second constant above the first store. */
#define SET_SIZE(p, v) do { *(p) = (v); } while (0)

/* two fixed buffer sizes (0x4000 and 0x700 bytes) and their sum */
int mpv_GetFixedWorkSizes(MwsfdCreInf *cprm, int *size_a, int *size_b) {
    SET_SIZE(size_a, 0x4000);
    SET_SIZE(size_b, 0x700);
    return *size_a + *size_b;
}

/* the slack mwPlyCalcWorkSfd adds for alignment */
int mwsfcre_GetAlignMargin(void) {
    return 256;
}

/* the sizes the player's work area is made of: input, MPV work, fixed work and the frame pool */
int mwPlyCalcWorkSfd(MwsfdCreInf *cprm) {
    int inBuf, f1, xBuf, mpv0, mpv1, mpv2;
    int frmSize, picBufSize;
    int fixedA, fixedB;
    int fixed, margin;
    int input, frames, size;

    mwsfcre_CalcWorkStmBuf(cprm, &inBuf, &f1, &xBuf, &mpv0, &mpv1, &mpv2);
    mwsfcre_CalcWorkFrmBuf(cprm, &frmSize, &picBufSize);
    fixed = mpv_GetFixedWorkSizes(cprm, &fixedA, &fixedB);
    margin = mwsfcre_GetAlignMargin();
    /* matching construct: statement-order search — the input and frame sums are formed before the main one */
    input = inBuf + mpv1;
    frames = frmSize + 0x40;
    frames += picBufSize + mpv2;
    size = f1 + xBuf + mpv0;
    size += 0x40;
    size += fixed;
    size += input;
    size += frames;
    size += margin;
    return size + 0x800;
}

/* the sfx work and, with additional information on, its SJ buffer */
int mwPlyCalcWorkCompo(MwsfdCreInf *cprm) {
    int size = MWSFSFX_CalcHnWorkSiz(cprm->maxWidth, cprm->maxHeight);

    if (MWSFTAG_IsUseAinfSj(cprm) == 1) {
        size += MWSFD_ADDINF_BUF_SIZE;
    }
    return size;
}

int mwPlyCalcWorkCprmSfd(MwsfdCreInf *cprm) {
    int size;

    if (cprm == 0) {
        MWSFSVM_Error(E1122613_mwPlyCalcWorkCprmSfd_cprm_is_NULL);
        return 0;
    }
    size = mwPlyCalcWorkSfd(cprm);
    return size + mwPlyCalcWorkCompo(cprm);
}

/* registers caller-owned frame buffers instead of allocating them per player */
void MPV_SetFrameBuffers(int num, int size, void **bufs) {
    int i;

    mpv_frm_buf_num = num;
    mpv_frm_buf_size = size;
    for (i = 0; i < num; i++)
        mpv_frm_buf_table[i] = bufs[i];
}

/* hands the SFD the SJ it reads from, described by where its buffer is */
void MWSFCRE_SetSupplySj(MwsfdPly *ply) {
    SfdSj *sj = ply->sj;
    void *sfd = ply->sfd;
    SfdSupplyPrm prm;

    if (sj == 0) {
        return;
    }
    if (sj == ply->memSj) {
        prm.kind = SFD_SUPPLY_MEM;
        prm.sj = sj;
        prm.buf = (unsigned int)ply->memBuf;
        prm.size = ply->memSize;
        prm.xsize = 0;
        prm.f20 = 0;
    } else if (sj == ply->defSj) {
        prm.kind = SFD_SUPPLY_INPUT_RING;
        prm.sj = sj;
        prm.buf = (unsigned int)ply->inputBuf;
        prm.size = ply->inputBufSize;
        prm.xsize = ply->inputXSize;
        prm.f20 = 0;
    } else {
        prm.kind = ply->srcType;
        prm.sj = sj;
        prm.buf = ply->srcBuf;
        prm.size = ply->srcSize;
        prm.xsize = ply->srcXSize;
        prm.f20 = 0;
    }
    if (SFD_SetSupplySj(sfd, &prm) != 0) {
        MWSFLIB_SetErrCode(-312);
        MWSFSVM_Error(E20010703B_MWSFCRE_SetSupplySj);
    }
}

/* matching construct: two orders tried: the buffer pointers read into locals first */
int mwsfcre_MallocRfb(MwsfdPly *ply, MwsfdCreInf *cprm, MwsfdFrmBufs *bufs) {
    int ret = 0;
    int size[2];
    int n;
    void *frm;
    void *dec;

    size[1] = 0x840D0;
    n = cprm->maxWidth * cprm->maxHeight;
    size[0] = n * 9 / 2 + 10304;
    if (mpv_frm_buf_num != 0) {
        if (mpv_frm_buf_num < 2 || mpv_frm_buf_size < size[0] || mpv_frm_buf_size < size[1]) {
            bufs->frm = 0;
            ret = -1;
            bufs->dec = 0;
        } else {
            frm = mpv_frm_buf_table[0];
            dec = mpv_frm_buf_table[1];
            bufs->dec = dec;
            bufs->frm = frm;
        }
    } else {
        bufs->frm = MWSFD_Malloc(ply, size[0]);
        bufs->dec = MWSFD_Malloc(ply, size[1]);
    }
    if (bufs->frm == 0 || bufs->dec == 0)
        ret = -1;
    return ret;
}

/* The pool of frame buffers for the decoder, the number of frames and the size of each held by the
 * creation parameters; the caller's table is used when one was registered. */
int mwsfcre_MallocTab(MwsfdPly *ply, MwsfdCreInf *cprm, void **frm) {
    int ret = 0;
    int width = cprm->maxWidth;
    int height = cprm->maxHeight;
    int mbWidth;
    int mbHeight;
    int fmt;
    int nfrm;
    int size;
    int i;

    nfrm = cprm->nfrmPoolWk;
    fmt = mwsfcre_ConvBufFmtFromMwsfd(cprm->bufFmt);
    mbWidth = width / 16;
    mbHeight = height / 16;
    size = (fmt == 2 ? mbWidth * mbHeight * 1024 : mbWidth * mbHeight * 384) + 64;
    if (mpv_frm_buf_num != 0) {
        if (mpv_frm_buf_num < nfrm + 2 || mpv_frm_buf_size < size) {
            ret = -1;
        } else {
            for (i = 0; i < nfrm; i++) {
                frm[i] = mpv_frm_buf_table[i + 2];
                if (frm[i] == 0) {
                    ret = -1;
                }
            }
        }
    } else {
        for (i = 0; i < nfrm; i++) {
            frm[i] = MWSFD_Malloc(ply, size);
            if (frm[i] == 0) {
                ret = -1;
            }
        }
    }
    return ret;
}

/* whether an output format is used as decoded (2 and 3 are converted) */
/* Creates the player's SFD handle: works out the buffer sizes, takes every buffer from the player's
 * work, fills the creation parameters of its file type and installs the error callback. */
void *mwsfcre_CreateSfd(MwsfdPly *ply, MwsfdCreInf *cprm) {
    void *cwk1;
    void *picusr_p;
    int mode = cprm->type;
    void *adxibuf_p;
    void *adxwk_p;
    int nfrm = cprm->nfrmPoolWk;
    int width = cprm->maxWidth;
    int height = cprm->maxHeight;
    SfdCrePrm crepara;
    MwsfdFrmBufs rfbbuf;
    void *frmtbl[16];
    int hnwksiz;
    int buf700siz;
    int rfbWidth;
    int rfbHeight;
    int cwidth;
    int cheight;
    void *cwk2;
    int rfbret;
    int frmret;
    void *hnwork_p;
    void *buf700_p;
    int fnamesiz;
    void *fname_p;
    int fmt;
    void *sfd;

    mwsfcre_CalcWorkStmBuf(cprm, &sjb, &sib, &vib, &aib, &adxibuf, &adxwk);
    mwsfcre_CalcWorkFrmBuf(cprm, &rfb, &tab);
    mpv_GetFixedWorkSizes(cprm, &hnwksiz, &buf700siz);
    fnamesiz = mwsfcre_GetAlignMargin();
    /* matching construct: expression search — the grouping orders the size globals' address registers */
    cwk1 = MWSFD_Malloc(ply, sib + (vib + aib + 64));
    cwk2 = MWSFD_Malloc(ply, sjb + 64);
    rfbret = mwsfcre_MallocRfb(ply, cprm, &rfbbuf);
    frmret = mwsfcre_MallocTab(ply, cprm, frmtbl);
    if (mwsfcre_IsOutFmtDirect(mode) == 1) {
        adxibuf_p = MWSFD_Malloc(ply, adxibuf);
        adxwk_p = MWSFD_Malloc(ply, adxwk);
    } else {
        adxibuf_p = 0;
        adxwk_p = 0;
    }
    picusr_p = MWSFD_Malloc(ply, 2048);
    hnwork_p = MWSFD_Malloc(ply, hnwksiz);
    buf700_p = MWSFD_Malloc(ply, buf700siz);
    fname_p = MWSFD_Malloc(ply, fnamesiz);
    if (cwk1 == 0 || cwk2 == 0 || rfbret != 0 || frmret != 0 || picusr_p == 0 || hnwork_p == 0 || fname_p == 0 ||
        buf700_p == 0) {
        MWSFSVM_Error(E2053002_not_enough_work);
        mwsfcre_AllFree(ply);
        return 0;
    }
    if (mwsfcre_IsOutFmtDirect(mode) == 1) {
        if (adxibuf_p == 0 || adxwk_p == 0) {
            MWSFSVM_Error(E4041301_not_enough_work);
            mwsfcre_AllFree(ply);
            return 0;
        }
    }
    mwsfd_sisjadr = ((unsigned int)cwk2 + 63) & ~63;
    mwsfcre_CalcFrmRes(cprm, &rfbWidth, &rfbHeight, &cwidth, &cheight);
    mwsfd_mpvpara.rfb_width = cwidth;
    mwsfd_mpvpara.rfb_height = cheight;
    mwsfd_mpvpara.max_width = rfbWidth;
    mwsfd_mpvpara.max_height = rfbHeight;
    mwsfd_mpvpara.rfb_adr = 0;
    mwsfd_mpvpara.frm_width = rfbWidth;
    mwsfd_mpvpara.frm_height = rfbHeight;
    mwsfd_mpvpara.count = nfrm;
    mwsfd_mpvpara.ta_adr = 0;
    mwsfd_adxtpara.buf = (char *)adxibuf_p;
    mwsfd_adxtpara.work = (char *)adxwk_p;
    switch (mode) {
    case 1:
        crepara = mwsfd_sfdmps_crepara;
        ply->inputBuf = (char *)mwsfd_sisjadr;
        ply->inputBufSize = sjb - mwsfd_option;
        ply->inputXSize = mwsfd_option;
        break;
    case 2:
        crepara = mwsfd_sfdmpv_crepara;
        ply->inputBuf = (char *)mwsfd_sisjadr;
        ply->inputBufSize = sjb - 2048;
        ply->inputXSize = 2048;
        break;
    case 3:
        crepara = mwsfd_vonlysfd_crepara;
        ply->inputBuf = (char *)mwsfd_sisjadr;
        ply->inputBufSize = sjb - mwsfd_option;
        ply->inputXSize = mwsfd_option;
        break;
    default:
        break;
    }
    crepara.unit = mwsfd_option;
    if (sib != 0) {
        sib = sib - sib % mwsfd_option;
    }
    fmt = mwsfcre_ConvBufFmtFromMwsfd(cprm->bufFmt);
    crepara.bufWork = (char *)cwk1;
    crepara.bufSize[0] = sib;
    crepara.bufSize[1] = vib;
    crepara.bufSize[2] = aib;
    crepara.nfrm = nfrm;
    crepara.width = width;
    crepara.height = height;
    crepara.bufFmt = (SfdBufFmt)fmt;
    crepara.work = (char *)hnwork_p;
    crepara.workSize = hnwksiz;
    SFD_SetMpvParaTbl(&mwsfd_mpvpara, (int *)&rfbbuf, (int *)frmtbl);
    switch (mode) {
    case 1:
        SFD_SetAdxtPara(&mwsfd_adxtpara);
        break;
    }
    SFD_SetSceMpeg(1);
    sfd = SFD_Create(&crepara, 0);
    if (sfd == 0) {
        MWSFLIB_SetErrCode(-305);
        MWSFSVM_Error(E20010703C_mwPlyCreateSofdec_create_error);
        return 0;
    }
    if (SFD_SetErrFn(sfd, MWSFLIB_SfdErrFunc, ply) != 0) {
        MWSFLIB_SetErrCode(-303);
        MWSFSVM_Error(E20010703D_mwPlyCreateSofdec_set_errcb);
        return 0;
    }
    ply->fname = fname_p;
    ply->fnameMax = fnamesiz;
    mwPlySetSysPicUsrBuf(ply, picusr_p, 2048, 64);
    return sfd;
}

int mwsfcre_IsOutFmtDirect(unsigned int format) {
    switch (format) {
    case 2:
    case 3:
        return 0;
    case 0:
    case 1:
    case 4:
    case 5:
    default:
        return 1;
    }
}

/* Installs the player's own picture user buffer: the part of `buf` past `offset` becomes the
 * built-in picture user buffer (unit = offset) and is made current; the first `offset` bytes are
 * kept as the user data buffer, and the current user data is cleared. */
void mwPlySetSysPicUsrBuf(MwsfdPly *ply, char *buf, int bufsize, int offset) {
    MwsfdPicUsrBuf *ub;
    int size;
    char *addr;

    /* matching construct: brute-force grouping — statement blocks in do/while(0) (loop notes are
     * scheduling barriers); retail keeps exactly this store order with the arithmetic hoisted */
    do { ub = &ply->sysPicUsrBuf; } while (0);
    do {
        size = bufsize - offset;
        addr = buf + offset;
        ply->udbufsize = offset;
        ply->udsize = 0;
    } while (0);
    do {
        ply->udbuf = buf;
        ply->ud = 0;
    } while (0);
    do {
        ply->picUsrBuf = ub;
        ub->size = size;
    } while (0);
    do {
        ub->unit = offset;
        ub->addr = addr;
    } while (0);
}

/* hands the current picture user buffer to SFD; it must hold (nfrmPoolWk + 4) units */
void mwsfcre_AttachPicUsrBuf(MwsfdPly *ply) {
    MwsfdPicUsrBuf *buf = ply->picUsrBuf;
    char *addr;
    int count;
    int unit;

    if (buf == 0) {
        MWSFSVM_Error(E02120501_Internal_Error_mwsfcre_AttachPicUsrBuf);
        return;
    }
    unit = buf->unit;
    count = ply->cre.nfrmPoolWk + 4;
    addr = buf->addr;
    if (buf->size < count * unit) {
        MWSFSVM_Error(E02120502_mwsfcre_AttachPicUsrBuf_usrdatbuf_is_short);
        return;
    }
    if (MWSFD_GetUsePicUsr() != 1)
        return;
    SFD_SetPicUsrBuf(ply->sfd, addr, count, unit);
}

/* Attaches a caller picture user buffer and makes it current, or with buf == 0 detaches it and
 * falls back to the built-in one. */
void mwPlyAttachPicUsrBuf(MwsfdPly *ply, char *buf, int size, int unit) {
    MwsfdPicUsrBuf *ub = &ply->attPicUsrBuf;
    MwsfdPicUsrBuf *sys = &ply->sysPicUsrBuf;

    if (buf == 0) {
        ub->addr = 0;
        ub->size = 0;
        ub->unit = 0;
        ply->picUsrBuf = sys;
    } else {
        if (size < (ply->cre.nfrmPoolWk + 4) * unit) {
            MWSFSVM_Error(mwPlyAttachPicUsrBuf_short_msg);
            return;
        }
        ub->addr = buf;
        ub->size = size;
        ub->unit = unit;
        ply->picUsrBuf = ub;
    }
    mwsfcre_AttachPicUsrBuf(ply);
}

void MWSFCRE_DestroySfd(void *sfd) {
    if (SFD_Destroy(sfd) != 0) {
        MWSFLIB_SetErrCode(-0x132);
        MWSFSVM_Error(E20010703E_MWSFCRE_DestroySfd);
    }
}

/* Sets the SFD handle up for the display: the decode conditions, and the frame period
 * (dispCycle * dispLatency * 1000, rounded to nearest) for conditions 45, 44 and 42. */
void MWSFCRE_SetCondSfd(MwsfdPly *ply, MwsfdCreInf *cprm, int dispCycle, int dispLatency) {
    void *sfd = ply->sfd;
    int nearest = 1; /* first the step-down flag, then the rounded value */
    float exact;
    int rounded;

    SFD_SetCond(sfd, 8, 0);
    SFD_SetCond(sfd, 1, 1);
    SFD_SetCond(sfd, 0, 0);
    SFD_SetCond(sfd, 23, 4);
    /* floor(x + 0.5): truncate, then step down when truncation went up */
    exact = (float)(dispCycle * dispLatency * 1000) + 0.5f;
    rounded = (int)exact;
    if (!(exact < (float)rounded)) {
        nearest = 0;
    }
    nearest = rounded - nearest; /* matching construct: manual — one variable for flag and result (retail reuses its register) */
    SFD_SetCond(sfd, 45, nearest);
    SFD_SetCond(sfd, 44, nearest);
    SFD_SetCond(sfd, 42, nearest);
    SFD_SetCond(sfd, 15, 2);
    SFD_SetCond(sfd, 51, 0);
    SFD_SetCond(sfd, 14, 0);
    SFD_SetCond(sfd, 28, 0);
    SFD_SetMpvCond(sfd, 5, 0);
}

/* stops the player's SFD handle, reinstalls the error callback and the picture user buffer */
int MWSFCRE_ResetSfdHn(MwsfdPly *ply) {
    void *sfd = ply->sfd;

    if (SFD_Stop(sfd) != 0) {
        MWSFSVM_Error(E0203261_MWSFCRE_ResetSfdHn_SFD_Stop_failed);
        return -1;
    }
    if (SFD_SetErrFn(sfd, MWSFLIB_SfdErrFunc, ply) != 0) {
        MWSFLIB_SetErrCode(-303);
        MWSFSVM_Error(E0203262_MWSFCRE_ResetSfdHn_SFD_SetErrFn_failed);
        return -1;
    }
    mwsfcre_AttachPicUsrBuf(ply);
    return 0;
}

SfdSj *mwsfcre_CreateSj(MwsfdPly *ply) {
    return SJRBF_Create(ply->inputBuf, ply->inputBufSize, ply->inputXSize);
}

/* Creates a player and wires every part of it: the SFD handle, the input SJs, the MWSTM stream, the link
 * controller, the sfx and the additional-information SJ. Any failure reports it and destroys the half-made
 * player. */
/* -1 when no work area is given and the malloc/free functions are not both set */
int mwsfcre_IsOkUsrMalloc(MwsfdCreInf *cprm) {
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();
    int result = 0;

    if (cprm->work == 0) {
        result = (work->mallocFn != 0) ? 0 : -1;
        if (work->freeFn == 0) {
            result = -1;
        }
    }
    return result;
}

/* the player allocates from the creation parameter's work area */
void mwsfcre_InitMemMng(MwsfdPly *ply, MwsfdCreInf *cprm) {
    MwsfdMemPool *pool = &ply->pool;
    void **blk = &ply->mallocBlk[MWSFD_MALLOC_MAX - 1];
    int i;

    pool->base = cprm->work;
    pool->size = cprm->workSize;
    pool->cur = cprm->work;
    pool->used = 0;
    ply->mallocCnt = 0;
    for (i = MWSFD_MALLOC_MAX - 1; i >= 0; i--) {
        *blk-- = 0;
    }
}

int mwsfcre_CheckCprm(MwsfdCreInf *cprm) {
    int ok = 1;

    if (cprm->type == 2) {
        MWSFSVM_Error(E3012100_M1V_Decode_is_not_support_yet);
        ok = 0;
    }
    if ((unsigned int)cprm->bufFmt >= 3U) {
        MWSFSVM_Error(E3012101_Buffer_format_is_invalid);
        ok = 0;
    }
    return ok;
}

/* allocates the sfx work and, with additional information on, its SJ buffer */
int mwsfcre_MallocCompoWork(MwsfdPly *ply) {
    MwsfdCreInf *cre = &ply->cre;
    int size = MWSFSFX_CalcHnWorkSiz(cre->maxWidth, cre->maxHeight);
    char *work = MWSFD_Malloc(ply, size);
    char *addInf;

    if (work == 0) {
        MWSFSVM_Error(E2053003_not_enough_work_sfx_wk);
        mwsfcre_AllFree(ply);
        return -1;
    }
    ply->sfxWork = work;
    ply->sfxWorkSize = size;
    if (MWSFTAG_IsUseAinfSj(cre) == 1) {
        addInf = MWSFD_Malloc(ply, MWSFD_ADDINF_BUF_SIZE);
        if (addInf == 0) {
            MWSFSVM_Error(E2053004_not_enough_work_ainfsj_buf);
            mwsfcre_AllFree(ply);
            return -1;
        }
        ply->addInfBase = addInf;
        ply->addInfSize = MWSFD_ADDINF_BUF_SIZE;
    } else {
        ply->addInfBase = 0;
        ply->addInfSize = 0;
    }
    return 0;
}

/* releases everything a player holds and returns its entry to the table */
void mwSfdDestroy(MwsfdPly *ply) {
    if (ply != 0) {
        mwSfdStopDec(ply);
        ply->used = 0;
        MWSFTAG_DestroyAinfSj(ply);
        if (ply->sfx != 0) {
            MWSFSFX_Destroy(ply->sfx);
        }
        if (ply->lsc != 0) {
            LSC_Destroy(ply->lsc);
        }
        if (ply->stm != 0) {
            MWSTM_Destroy(ply->stm);
        }
        if (ply->defSj != 0) {
            ply->defSj->vtbl->destroy(ply->defSj);
        }
        if (ply->memSj != 0) {
            ply->memSj->vtbl->destroy(ply->memSj);
        }
        if (ply->sfd != 0) {
            MWSFCRE_DestroySfd(ply->sfd);
        }
        MWSST_Destroy(&ply->sst);
        mwsfcre_AllFree(ply);
        if (mwsfcre_GetMallocCnt(ply) != 0) {
            MWSFSVM_Error(E2053005_forgot_free);
        }
        memset(ply, 0, sizeof(MwsfdPly));
        ply->used = 0;
        ply->vtbl = &mwply_vtbl;
    }
}

void mwsfd_SetOption(int value) {
    mwsfd_option = value;
}

/* matching construct: 120-order sweep of the field copies */
void mwPlyGetHdrInf(char *buf, int size, MwsfdHdrInf *out) {
    MwsfdHdrInf hdr;
    SfdAnaInf inf;

    if (buf == 0 || out == 0) {
        MWSFSVM_Error(E204161_mwPlyGetHdrInf_NULL_pointer);
        return;
    }
    if (size <= 0) {
        MWSFSVM_Error(E204162_mwPlyGetHdrInf_bufsize_error);
        return;
    }
    memset(&hdr, 0, sizeof(hdr));
    SFD_AnalyCreInf(buf, size, &inf);
    if (inf.found == 0 || inf.isAv == 0) {
        *out = hdr;
        out->valid = 0;
        return;
    }
    hdr.type = mwsfcre_DecideFtypeByHdrInf(&inf);
    hdr.width = inf.width;
    hdr.height = inf.height;
    hdr.rate = inf.frameRate;
    hdr.audioFreq = inf.sfreq;
    hdr.f40 = inf.nch;
    mwply_GetPicInf(buf, size, &hdr);
    hdr.valid = mwsfdcre_IsPlayableByHdrInf(&hdr);
    *out = hdr;
}

/* the MWSFD file type: an SFD system stream 1, one without audio 3, an MPEG video stream 2, else 0 */
int mwsfcre_DecideFtypeByHdrInf(SfdAnaInf *inf) {
    int kind = 0;

    if (inf->system == 0) {
        if (inf->video != 0) {
            if (inf->audio == 0) {
                kind = 2;
            }
        }
    } else {
        kind = (inf->audio == 0) ? 3 : 1;
    }
    return kind;
}

/* a stream the library can play: not audio alone, and with video and audio only the sample rates it mixes */
int mwsfdcre_IsPlayableByHdrInf(MwsfdHdrInf *hdr) {
    if (hdr->type == 0) return 0;
    if (hdr->type == 2) return 0;
    if (hdr->type == 1) {
        switch (hdr->audioFreq) {
        case 0: case 6000: case 12000: case 24000: case 48000: break;
        default: return 0;
        }
    }
    return 1;
}

void mwPlySetMallocFn(void *(*mallocFn)(void *obj, int size), void (*freeFn)(void *obj, void *ptr),
                         void *obj) {
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    work->mallocFn = mallocFn;
    work->freeFn = freeFn;
    work->mallocObj = obj;
}

/* from the player's pool when it has one, else through the installed malloc function; each block is
 * recorded for mwsfcre_AllFree */
void *MWSFD_Malloc(MwsfdPly *ply, int size) {
    void *block;

    if (ply->mallocCnt >= MWSFD_MALLOC_MAX) {
        MWSFSVM_Error(E2053001_MWSFD_Malloc_cnt_over);
        return 0;
    }
    if (size < 0) {
        return 0;
    }
    if (ply->pool.base != 0) {
        block = mwsfcre_OrgMalloc(ply, size);
    } else {
        block = mwsfcre_UsrMalloc(size);
    }
    if (block != 0) {
        ply->mallocBlk[ply->mallocCnt] = block;
        mwsfcre_IncMallocCnt(ply);
    }
    return block;
}

void *mwsfcre_OrgMalloc(MwsfdPly *ply, int size) {
    MwsfdMemPool *pool = &ply->pool;
    unsigned int used = pool->used + size;
    char *block = 0;

    if ((unsigned int)pool->size >= used) {
        block = pool->cur;
        pool->used = used;
        pool->cur = block + size;
    }
    return block;
}

void *mwsfcre_UsrMalloc(int size) {
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    return work->mallocFn(work->mallocObj, size);
}

void MWSFD_Free(MwsfdPly *ply, void *ptr) {
    if (ply->pool.base != 0) {
        mwsfcre_OrgFree(ply, ptr);
    } else {
        mwsfcre_UsrFree(ptr);
    }
    mwsfcre_DecMallocCnt(ply);
}

/* the pool is released as a whole */
void mwsfcre_OrgFree(MwsfdPly *ply, void *ptr) {
}

void mwsfcre_UsrFree(void *ptr) {
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    work->freeFn(work->mallocObj, ptr);
}

void mwsfcre_AllFree(MwsfdPly *ply) {
    void **blk = &ply->mallocBlk[MWSFD_MALLOC_MAX - 1];
    int i;

    for (i = MWSFD_MALLOC_MAX - 1; i >= 0; i--) {
        if (*blk != 0) {
            MWSFD_Free(ply, *blk);
            *blk = 0;
        }
        blk--;
    }
}

int mwsfcre_IncMallocCnt(MwsfdPly *ply) {
    return ++ply->mallocCnt;
}

int mwsfcre_DecMallocCnt(MwsfdPly *ply) {
    return --ply->mallocCnt;
}

int mwsfcre_GetMallocCnt(MwsfdPly *ply) {
    return ply->mallocCnt;
}
