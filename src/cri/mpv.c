/* CRI MPV (M2V/PS2EE) decoder library: initialisation, the handle pool, conditions, the bridge to the
 * lower-layer decoder and the 64-bit multiply-divide helpers. */
#include "dw4/cri/mpv.h"

extern char cri_mpv_version[];
extern MpvBuildInf mpv_build_inf;
extern unsigned char mpv_endian_mark[4]; /* 4, 3, 2, 1 */
extern int mpv_default_cond[MPV_COND_MAX];
extern MpvLib mpv_lib;
extern MpvHn *mpv_cur_hn;               /* the handle last given to mpv_CheckHn */
extern int mpv_lower_work[];            /* 0x3840 bytes for the lower layer */
extern unsigned char mpv_clamp_table[1024];
extern unsigned char *mpv_clamp;        /* mpv_clamp_table + 384 */

unsigned char *MPV_SearchDelim(unsigned char *data, int size, int code);
int mpvsc_GetKind(unsigned char *p);
int mpv_ReportError(void *hn, int error);
void mpsutl_CopyWords(void *dst, const void *src, int words);
void mpsutl_FillWords(void *dst, int value, int size);
void mpv_ResetErr(MpvErrObj *err);
void mpv_SetBufEnt(MpvHn *hn, int index, int a, int b, int c);
void mpv_SetLowSize(MpvHn *hn, int a, int b);
int mpvhook_IsInstalled(void);
void mpvhook_Init(int n, void *work, int size);
void mpv_InstallHooks(void);
void mpvhook_Finish(void);
int mpvhook_Create(MpvHn *hn);
void mpvhook_Destroy(int lower);
void mpvhook_SetCond(int lower, int no, int value);
void mpvhook_SetBufEnt(int lower, int index, int addr, int a, int b);
void mpvhook_SetSize(int lower, int width, int height);
void mpvhook_SetFlagPtr(int lower, int zero, int *flag);
int mpvhook_Start(int lower, int arg);
void mpvhook_GetPicInf(int lower, MpvPicInf *inf);
void mpvhook_GetInf(int lower, int *a);
void mpvhook_GetRate(int lower, int *a, int *b, int *c);
void mpvhook_GetDispSize(int lower, int *a, int *b);
long long __muldi3(long long a, long long b);

int mpv_IsLowerReady(void);
void mpv_BuildClampTable(void);
void mpv_FinishLower(void);
void mpv_ReleaseMem(void *p, int size);
void mpv_ClearMem(void *p, int size);
MpvHn *mpv_SearchFreeHn(void);
MpvHn *mpv_InitHn(MpvHn *hn);
int mpv_CreateLower(MpvHn *hn);
void mpv_BindHnBuffers(MpvHn *hn);
void mpv_ResetPicInf(MpvPicInf *inf);
int mpv_CheckHn(MpvHn *hn);
void mpv_DestroyLower(MpvHn *hn);
void mpv_NullCbFn(void);
void mpvlib_SetCondAll(int no, int value);
void mpv_SetLowerCond(MpvHn *hn, int no, int value);
void mpv_GetLowerInf(MpvHn *hn);
int UTY_MulDiv(int a, int b, int c);

char *MPV_GetVersionStr(void) {
    return cri_mpv_version;
}

/* whether a stream is decodable here: the picture start code (0x00000140 group) is found and, unless the
 * lower layer is up, the following start code does not carry flag 0x10 */
int MPV_IsConformable(unsigned char *data, int size) {
    unsigned char *p = MPV_SearchDelim(data, size, 64);

    if (p == 0) {
        return 0;
    }
    if (mpv_IsLowerReady() != 0) {
        return 1;
    }
    p += 4;
    size -= p - data;
    if (size <= 0) {
        return 0;
    }
    p = MPV_SearchDelim(p, size, -1);
    if (p == 0) {
        return 0;
    }
    if (mpvsc_GetKind(p) & 0x10) {
        return 0;
    }
    return 1;
}

int mpv_CheckLibIntegrity(void) {
    if (mpv_build_inf.magic != 0x5a5a5a5a) {
        return mpv_ReportError(0, 0xff03ff02);
    }
    if (mpv_endian_mark[0] != 4) {
        for (;;) {
            ((void (*)(void))-1)();
        }
    }
    return 0;
}

void mpv_InitStatus(int status) {
}

int mpv_AddOptionFlag(int flags) {
    if (mpv_lib.optionFlag != 0) {
        flags |= 0x02000000;
    }
    return flags;
}

int mpv_AddInitFlag(int flags) {
    if (mpv_lib.initFlag != 0) {
        flags |= 0x02000000;
    }
    return flags;
}

/* builds the saturation table, then keeps a copy at `copy` and points mpv_clamp at the copy's centre */
void mpv_InitClampTable(unsigned char *copy) {
    mpv_BuildClampTable();
    if (copy != 0) {
        mpsutl_CopyWords(copy, mpv_clamp_table, 256);
        mpv_clamp = copy + 384;
    }
}

/* 384 zeros, the ramp 0..255 and 384 x 0xFF: mpv_clamp[v] saturates v in -384..639 to 0..255 */
void mpv_BuildClampTable(void) {
    unsigned char *p = mpv_clamp_table;
    int i;

    for (i = 0; i < 384; i++) {
        *p++ = 0;
    }
    for (i = 0; i < 256; i++) {
        *p++ = i;
    }
    for (i = 0; i < 384; i++) {
        *p++ = 0xFF;
    }
    mpv_clamp = &mpv_clamp_table[384];
}

void mpv_FreeAllHn(void) {
    MpvHn *hn = mpv_lib.hn;
    int nhn = mpv_lib.nhn;
    int i;

    for (i = 0; i < nhn; i++, hn++) {
        hn->stat = MPV_HN_FREE;
    }
}

void mpv_BindHnBuffers(MpvHn *hn) {
    char *pool = mpv_lib.pool;

    hn->mbBuf = pool + 4384;
    hn->blkBuf = pool + 4352;
    hn->dctBuf = pool + 4448;
    hn->clampY = mpv_clamp;
    hn->clampC = mpv_clamp;
}

void mpv_InitHw(MpvLib *pool) {
}

/* matching construct: 72-variant sweep — store order and declarations */
void mpv_InitWork(int nhn, char *work) {
    char *base;
    char *tables;
    char *pool;

    base = (char *)(((int)work + 63) & ~63);
    mpsutl_FillWords(base, 0, (nhn << 8) + 0x800);
    tables = base + (nhn << 10);
    pool = tables + 0x420;
    mpv_ClearMem(pool, MPV_POOL_SIZE);
    mpsutl_CopyWords(&mpv_lib, mpv_default_cond, MPV_COND_MAX);
    mpv_lib.tables = tables;
    mpv_lib.pool = pool;
    mpv_lib.nhn = nhn;
    mpv_lib.hn = (MpvHn *)base;
}

void mpv_ResetPicInf(MpvPicInf *inf) {
    inf->f0 = 0;
    inf->f4 = 0;
    inf->f8 = 0;
    inf->f12 = 0;
    inf->f16 = 0;
    inf->f20 = 0;
    inf->f24 = 0;
    inf->f28 = 0;
    inf->f32 = 0;
    inf->f36 = 0;
    inf->f40 = 0;
    inf->f44 = 0;
    inf->f48 = 0;
    inf->f52 = 0;
    inf->f56 = 3;
    inf->f60 = 1;
    inf->f64 = 1;
    inf->f68 = 1;
    inf->f72 = 0;
    inf->f76 = 0;
    inf->f80 = -1;
    inf->f82 = -1;
    inf->f84 = 0;
    inf->f85 = -1;
    inf->f86 = -1;
    inf->f87 = -1;
    inf->f88 = 0;
    inf->f89 = 1;
    inf->f90 = 0;
    inf->f91 = 0;
    inf->f92 = 0;
    inf->f93 = -1;
    inf->f94 = -1;
    inf->f95 = -1;
    inf->f96 = -1;
    inf->f97 = 0;
    inf->f98 = -1;
    inf->f99 = -1;
    inf->f100 = -1;
}

void MPV_Finish(void) {
    mpv_FinishLower();
    mpv_ReleaseMem(mpv_lib.pool, MPV_POOL_SIZE);
}

MpvHn *MPV_Create(void) {
    MpvHn *hn;

    hn = mpv_SearchFreeHn();
    if (hn == 0) {
        return 0;
    }
    mpv_ClearMem(hn, MPV_HN_SIZE);
    hn = mpv_InitHn(hn);
    hn->lower = mpv_CreateLower(hn);
    return hn;
}

MpvHn *mpv_SearchFreeHn(void) {
    MpvHn *hn = mpv_lib.hn;
    int nhn = mpv_lib.nhn;
    int i;

    for (i = 0; i < nhn; i++, hn++) {
        if (hn->stat == MPV_HN_FREE) {
            return hn;
        }
    }
    return 0;
}

MpvHn *mpv_InitHn(MpvHn *hn) {
    int i;

    mpv_BindHnBuffers(hn);
    hn->f396 = 0;
    mpsutl_CopyWords(hn->cond, mpv_lib.cond, MPV_COND_MAX);
    mpv_ResetErr(&hn->err);
    mpv_ResetPicInf(&hn->picInf);
    hn->skipReq = 0;
    hn->skipCnt = 0;
    hn->maxCount = hn->cond[7];
    hn->strmType = 0;
    hn->f860 = 0;
    hn->f864 = 0;
    hn->f868 = 0;
    hn->idcPrec = 0;
    for (i = 0; i < 4; i++) {
        mpv_SetBufEnt(hn, i, 0, 0, 0);
    }
    mpv_SetLowSize(hn, 0, 0);
    hn->stat = MPV_HN_USED;
    return hn;
}

void MPV_GetPicSize(MpvHn *hn, int *width, int *height) {
    MpvSeqInf *seq = &hn->seq;

    *width = seq->width;
    *height = seq->height;
}

int MPV_Destroy(MpvHn *hn) {
    if (mpv_CheckHn(hn) != 0) {
        return mpv_ReportError(0, 0xFF030201);
    }
    mpv_DestroyLower(hn);
    mpv_ReleaseMem(hn, MPV_HN_SIZE);
    hn->stat = MPV_HN_FREE;
    return 0;
}

void mpv_ClearMem(void *p, int size) {
}

void mpv_ReleaseMem(void *p, int size) {
}

void mpv_NullCbFn(void) {
}

/* sets condition `no` of a handle, or with no handle the default of every new and every live handle */
int MPV_SetCond(MpvHn *hn, int no, int value) {
    int *cond;

    if (no == MPV_COND_CBFN && value == 0) {
        value = (int)mpv_NullCbFn;
    }
    if (hn == 0) {
        mpvlib_SetCondAll(no, value);
        cond = mpv_lib.cond;
    } else {
        if (mpv_CheckHn(hn) != 0) {
            return mpv_ReportError(0, 0xFF030202);
        }
        cond = hn->cond;
    }
    cond[no] = value;
    mpv_SetLowerCond(hn, no, value);
    return 0;
}

void mpvlib_SetCondAll(int no, int value) {
    MpvHn *hn = mpv_lib.hn;
    int nhn = mpv_lib.nhn;
    int i;

    for (i = 0; i < nhn; i++, hn++) {
        if (hn->stat == MPV_HN_USED) {
            hn->cond[no] = value;
        }
    }
}

int MPV_GetCond(MpvHn *hn, int no, int *value) {
    int *cond;

    if (hn == 0) {
        cond = mpv_lib.cond;
    } else {
        if (mpv_CheckHn(hn) != 0) {
            return mpv_ReportError(0, 0xFF030210);
        }
        cond = hn->cond;
    }
    *value = cond[no];
    return 0;
}

int mpv_CheckHn(MpvHn *hn) {
    mpv_cur_hn = hn;
    if (hn == 0) {
        return -1;
    }
    if (hn->stat != MPV_HN_USED) {
        return -1;
    }
    return 0;
}

int mpv_IsLowerReady(void) {
    return mpvhook_IsInstalled();
}

void mpv_InitLower(void) {
    mpv_InstallHooks();
    mpvhook_Init(8, mpv_lower_work, 0x3840);
}

void mpv_FinishLower(void) {
    mpvhook_Finish();
}

int mpv_CreateLower(MpvHn *hn) {
    return mpvhook_Create(hn);
}

void mpv_DestroyLower(MpvHn *hn) {
    mpvhook_Destroy(hn->lower);
}

void mpv_SetLowerCond(MpvHn *hn, int no, int value) {
    int lower = 0;

    if (hn != 0) {
        lower = hn->lower;
    }
    mpvhook_SetCond(lower, no, value);
}

/* hands the handle's buffers to the lower layer and starts it; -1 without a lower layer, -2 when it
 * refuses */
int mpv_StartLower(MpvHn *hn, int arg) {
    MpvBufEnt *ent;
    int i;

    if (mpvhook_IsInstalled() != 0) {
        for (i = 0, ent = hn->bufEnt; i < 4; i++) {
            mpvhook_SetBufEnt(hn->lower, i, ent->addr, ent->f4, ent->f8);
            ent++;
        }
        mpvhook_SetSize(hn->lower, hn->low.width, hn->low.height);
        if (mpvhook_Start(hn->lower, arg) != 0) {
            return -2;
        }
        mpvhook_SetFlagPtr(hn->lower, 0, &hn->low.flag);
        mpv_GetLowerInf(hn);
        return 0;
    }
    return -1;
}

/* matching construct: 120-order sweep of the five field stores */
void mpv_GetLowerInf(MpvHn *hn) {
    MpvPicInf inf;
    int a;
    int b, c, d;
    int e, f;

    mpvhook_GetPicInf(hn->lower, &inf);
    mpvhook_GetInf(hn->lower, &a);
    mpvhook_GetRate(hn->lower, &b, &c, &d);
    mpvhook_GetDispSize(hn->lower, &e, &f);
    hn->picInf = inf;
    hn->lowInf0 = a;
    hn->lowInf1 = b / 2048;
    hn->lowInf2 = c;
    hn->lowInf3 = e;
    hn->lowInf4 = f;
}

int mpv_MulDiv(int a, int b, int c) {
    return UTY_MulDiv(a, b, c);
}

/* a * b / c through a 64-bit product; c == 0 saturates to INT_MIN/INT_MAX by the sign of a * b */
int UTY_MulDiv(int a, int b, int c) {
    if (c == 0) {
        return ((a ^ b) < 0) ? (int)0x80000000 : 0x7FFFFFFF;
    }
    return (long)a * b / c;
}

/* a * b / c rounded to nearest on magnitudes, the sign restored; c == 0 saturates as UTY_MulDiv */
int UTY_MulDivRound(long long a, long long b, long long c) {
    int sign;
    long long d;

    if (c == 0) {
        return ((a ^ b) < 0) ? 0x80000000 : 0x7fffffff;
    }
    d = c;
    sign = 1;
    if (a < 0) {
        sign = -1;
        a = -a;
    }
    if (b < 0) {
        sign = -sign;
        b = -b;
    }
    if (d < 0) {
        d = -d;
        sign = -sign;
    }
    a = (__muldi3(a, b) + d / 2) / d;
    if (sign < 0) {
        a = -a;
    }
    return a;
}

/* the 64-bit result of UTY_MulDivRound; c == 0 saturates to the 64-bit limit of the result's sign */
long long UTY_MulDivRound64(long long a, long long b, long long c) {
    int sign;

    if (c == 0) {
        return ((a ^ b) >= 0) ? 0x7FFFFFFFFFFFFFFFLL : (long long)0x8000000000000000ULL;
    }
    sign = 1;
    if (a < 0) {
        sign = -1;
        a = -a;
    }
    if (b < 0) {
        sign = -sign;
        b = -b;
    }
    if (c < 0) {
        c = -c;
        sign = -sign;
    }
    a = (__muldi3(a, b) + c / 2) / c;
    return (sign < 0) ? -a : a;
}
