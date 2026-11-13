/* CRI MWSFD player creation (MWSFCRE): work-area sizes, the frame and picture user buffers, the SFD
 * handle set-up and teardown, mwPlyGetHdrInf and the player's work-area allocator (MWSFD_Malloc). */
#include "dw4/cri/mwsfd.h"
#include "dw4/cri/sfdsj.h"

#define MWSFD_MALLOC_MAX 32
#define MWSFD_ADDINF_BUF_SIZE 0x20000

/* the two buffers a player decodes into */
typedef struct MwsfdFrmBufs {
    void *frm;  /* the frame pool: width * height * 9 / 2 + 10304 bytes */
    void *dec;  /* the decoder's fixed work */
} MwsfdFrmBufs;

/* what mwPlyGetHdrInf reports */
typedef struct MwsfdHdrInf {
    int valid;
    int type;     /* mwsfcre_GetHdrType */
    int width;
    int height;
    int rate;
    int f20;
    int f24;
    int f28;
    int f32;
    int frames;
    int f40;
} MwsfdHdrInf;

/* the SFD header analysis mwPlyGetHdrInf reads */
typedef struct SfdHdrInf {
    signed char ok0;
    signed char ok1;
    char pad2[2];
    int video;    /* 4 */
    int audio;    /* 8 */
    int f12;      /* 12 */
    int f16;
    int width;    /* 20 */
    int height;   /* 24 */
    int f28;
    int rate;     /* 32 */
    int f36;
    signed char f40;
    char pad41[3];
    int frames;   /* 44 */
    int pad48[4];
} SfdHdrInf;

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

void *memset(void *s, int c, unsigned int n);
void mwsfd_Error(const char *msg);
void MWSFLIB_SetErrCode(int code);
int MWSFD_GetUsePicUsr(void);
void MWSFLIB_SfdErrFunc(void);
void mwSfdStopDec(MwsfdPly *ply);
void mwply_GetPicInf(char *buf, int size, MwsfdHdrInf *hdr);
int mwsfsfx_CalcWorkSize(int width, int height);
void mwsfsfx_Destroy(void *sfx);
int mwsfd_IsAddInfOn(MwsfdCreInf *cprm);
void mwsfd_DestroyAddInfSj(MwsfdPly *ply);
void MWSTM_Destroy(void *stm);
void MWSST_Destroy(MwsfdSst *sst);
void LSC_Destroy(struct LscObj *lsc);
SfdSj *SJRBF_Create(char *buf, int size, int xsize);
int SFD_Destroy(void *sfd);
int SFD_Stop(void *sfd);
int SFD_SetErrFn(void *sfd, void (*fn)(void), void *obj);
void SFD_SetCond(void *sfd, int no, int value);
void SFD_SetMpvCond(void *sfd, int no, int value);
void SFD_SetPicUsrBuf(void *sfd, char *addr, int count, int unit);
void SFD_GetHdrInf(char *buf, int size, SfdHdrInf *inf);

int mwsfcre_CalcMpvWorkSize(MwsfdCreInf *cprm);
int mwsfcre_CalcSfxWorkSize(MwsfdCreInf *cprm);
void *MWSFD_Malloc(MwsfdPly *ply, int size);
void *mwsfd_PoolMalloc(MwsfdPly *ply, int size);
void *mwsfd_UsrMalloc(int size);
int mwsfd_IncMallocCnt(MwsfdPly *ply);
int mwsfd_DecMallocCnt(MwsfdPly *ply);
int mwsfd_GetMallocCnt(MwsfdPly *ply);
void mwsfd_PoolFree(MwsfdPly *ply, void *ptr);
void mwsfd_UsrFree(void *ptr);
void mwsfd_FreeAll(MwsfdPly *ply);
int mwsfcre_GetHdrType(SfdHdrInf *inf);
int mwsfcre_IsHdrValid(MwsfdHdrInf *hdr);

/* matching construct: permuter, reduced by hand: the type read in each test */
void mwsfcre_CalcMpvWorkSizes(MwsfdCreInf *cprm, int *inBuf, int *f1, int *xBuf, int *mpv0, int *mpv1,
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
void mwsfcre_GetPicSizes(MwsfdCreInf *cprm, int *width, int *height, int *halfWidth, int *halfHeight) {
    int w = cprm->maxWidth;
    int h = cprm->maxHeight;

    *halfWidth = (w / 2 + 31) / 32 * 32;
    *halfHeight = h / 2;
    *width = w;
    *height = h;
}

/* the internal buffer format of a creation parameter's one */
int mwsfcre_ConvBufFmt(int format) {
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
        mwsfd_Error(E206011_MwsfdCrePrm_illigal_buffmt);
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

/* the slack mwsfcre_CalcMpvWorkSize adds for alignment */
int mwsfcre_GetAlignMargin(void) {
    return 256;
}

/* the sfx work and, with additional information on, its SJ buffer */
int mwsfcre_CalcSfxWorkSize(MwsfdCreInf *cprm) {
    int size = mwsfsfx_CalcWorkSize(cprm->maxWidth, cprm->maxHeight);

    if (mwsfd_IsAddInfOn(cprm) == 1) {
        size += MWSFD_ADDINF_BUF_SIZE;
    }
    return size;
}

int mwPlyCalcWorkCprmSfd(MwsfdCreInf *cprm) {
    int size;

    if (cprm == 0) {
        mwsfd_Error(E1122613_mwPlyCalcWorkCprmSfd_cprm_is_NULL);
        return 0;
    }
    size = mwsfcre_CalcMpvWorkSize(cprm);
    return size + mwsfcre_CalcSfxWorkSize(cprm);
}

/* registers caller-owned frame buffers instead of allocating them per player */
void MPV_SetFrameBuffers(int num, int size, void **bufs) {
    int i;

    mpv_frm_buf_num = num;
    mpv_frm_buf_size = size;
    for (i = 0; i < num; i++)
        mpv_frm_buf_table[i] = bufs[i];
}

/* matching construct: two orders tried: the buffer pointers read into locals first */
int mwsfcre_AllocFrmBufs(MwsfdPly *ply, MwsfdCreInf *cprm, MwsfdFrmBufs *bufs) {
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

/* whether an output format is used as decoded (2 and 3 are converted) */
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
        mwsfd_Error(E02120501_Internal_Error_mwsfcre_AttachPicUsrBuf);
        return;
    }
    unit = buf->unit;
    count = ply->cre.nfrmPoolWk + 4;
    addr = buf->addr;
    if (buf->size < count * unit) {
        mwsfd_Error(E02120502_mwsfcre_AttachPicUsrBuf_usrdatbuf_is_short);
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
            mwsfd_Error(mwPlyAttachPicUsrBuf_short_msg);
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
        mwsfd_Error(E20010703E_MWSFCRE_DestroySfd);
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
        mwsfd_Error(E0203261_MWSFCRE_ResetSfdHn_SFD_Stop_failed);
        return -1;
    }
    if (SFD_SetErrFn(sfd, MWSFLIB_SfdErrFunc, ply) != 0) {
        MWSFLIB_SetErrCode(-303);
        mwsfd_Error(E0203262_MWSFCRE_ResetSfdHn_SFD_SetErrFn_failed);
        return -1;
    }
    mwsfcre_AttachPicUsrBuf(ply);
    return 0;
}

SfdSj *mwsfcre_CreateInputSj(MwsfdPly *ply) {
    return SJRBF_Create(ply->inputBuf, ply->inputBufSize, ply->inputXSize);
}

/* -1 when no work area is given and the malloc/free functions are not both set */
int mwsfcre_CheckMallocFn(MwsfdCreInf *cprm) {
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
void mwsfcre_InitMemPool(MwsfdPly *ply, MwsfdCreInf *cprm) {
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
        mwsfd_Error(E3012100_M1V_Decode_is_not_support_yet);
        ok = 0;
    }
    if ((unsigned int)cprm->bufFmt >= 3U) {
        mwsfd_Error(E3012101_Buffer_format_is_invalid);
        ok = 0;
    }
    return ok;
}

/* allocates the sfx work and, with additional information on, its SJ buffer */
int mwsfcre_AllocSfxWork(MwsfdPly *ply) {
    MwsfdCreInf *cre = &ply->cre;
    int size = mwsfsfx_CalcWorkSize(cre->maxWidth, cre->maxHeight);
    char *work = MWSFD_Malloc(ply, size);
    char *addInf;

    if (work == 0) {
        mwsfd_Error(E2053003_not_enough_work_sfx_wk);
        mwsfd_FreeAll(ply);
        return -1;
    }
    ply->sfxWork = work;
    ply->sfxWorkSize = size;
    if (mwsfd_IsAddInfOn(cre) == 1) {
        addInf = MWSFD_Malloc(ply, MWSFD_ADDINF_BUF_SIZE);
        if (addInf == 0) {
            mwsfd_Error(E2053004_not_enough_work_ainfsj_buf);
            mwsfd_FreeAll(ply);
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
void mwsfcre_DestroyPly(MwsfdPly *ply) {
    if (ply != 0) {
        mwSfdStopDec(ply);
        ply->used = 0;
        mwsfd_DestroyAddInfSj(ply);
        if (ply->sfx != 0) {
            mwsfsfx_Destroy(ply->sfx);
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
        mwsfd_FreeAll(ply);
        if (mwsfd_GetMallocCnt(ply) != 0) {
            mwsfd_Error(E2053005_forgot_free);
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
    SfdHdrInf inf;

    if (buf == 0 || out == 0) {
        mwsfd_Error(E204161_mwPlyGetHdrInf_NULL_pointer);
        return;
    }
    if (size <= 0) {
        mwsfd_Error(E204162_mwPlyGetHdrInf_bufsize_error);
        return;
    }
    memset(&hdr, 0, sizeof(hdr));
    SFD_GetHdrInf(buf, size, &inf);
    if (inf.ok0 == 0 || inf.ok1 == 0) {
        *out = hdr;
        out->valid = 0;
        return;
    }
    hdr.type = mwsfcre_GetHdrType(&inf);
    hdr.width = inf.width;
    hdr.height = inf.height;
    hdr.rate = inf.rate;
    hdr.frames = inf.frames;
    hdr.f40 = inf.f40;
    mwply_GetPicInf(buf, size, &hdr);
    hdr.valid = mwsfcre_IsHdrValid(&hdr);
    *out = hdr;
}

/* video with audio 1, video alone 3, audio alone 2, else 0 */
int mwsfcre_GetHdrType(SfdHdrInf *inf) {
    int kind = 0;

    if (inf->video == 0) {
        if (inf->audio != 0) {
            if (inf->f12 == 0) {
                kind = 2;
            }
        }
    } else {
        kind = (inf->f12 == 0) ? 3 : 1;
    }
    return kind;
}

void MWSFD_SetMallocFunc(void *(*mallocFn)(void *obj, int size), void (*freeFn)(void *obj, void *ptr),
                         void *obj) {
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    work->mallocFn = mallocFn;
    work->freeFn = freeFn;
    work->mallocObj = obj;
}

/* from the player's pool when it has one, else through the installed malloc function; each block is
 * recorded for mwsfd_FreeAll */
void *MWSFD_Malloc(MwsfdPly *ply, int size) {
    void *block;

    if (ply->mallocCnt >= MWSFD_MALLOC_MAX) {
        mwsfd_Error(E2053001_MWSFD_Malloc_cnt_over);
        return 0;
    }
    if (size < 0) {
        return 0;
    }
    if (ply->pool.base != 0) {
        block = mwsfd_PoolMalloc(ply, size);
    } else {
        block = mwsfd_UsrMalloc(size);
    }
    if (block != 0) {
        ply->mallocBlk[ply->mallocCnt] = block;
        mwsfd_IncMallocCnt(ply);
    }
    return block;
}

void *mwsfd_PoolMalloc(MwsfdPly *ply, int size) {
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

void *mwsfd_UsrMalloc(int size) {
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    return work->mallocFn(work->mallocObj, size);
}

void MWSFD_Free(MwsfdPly *ply, void *ptr) {
    if (ply->pool.base != 0) {
        mwsfd_PoolFree(ply, ptr);
    } else {
        mwsfd_UsrFree(ptr);
    }
    mwsfd_DecMallocCnt(ply);
}

/* the pool is released as a whole */
void mwsfd_PoolFree(MwsfdPly *ply, void *ptr) {
}

void mwsfd_UsrFree(void *ptr) {
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    work->freeFn(work->mallocObj, ptr);
}

void mwsfd_FreeAll(MwsfdPly *ply) {
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

int mwsfd_IncMallocCnt(MwsfdPly *ply) {
    return ++ply->mallocCnt;
}

int mwsfd_DecMallocCnt(MwsfdPly *ply) {
    return --ply->mallocCnt;
}

int mwsfd_GetMallocCnt(MwsfdPly *ply) {
    return ply->mallocCnt;
}
