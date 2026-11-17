/* CRI MPV (M2V/PS2EE) decoder library: initialisation, the handle pool, conditions, the bridge to the
 * lower-layer decoder and the 64-bit multiply-divide helpers. */
#include "dw4/cri/mpv.h"
#include "dw4/cri/mps.h"
#include "dw4/cri/uty.h"
#include "dw4/support/softfloat.h"

extern char cri_mpv_version[];
extern char *volatile mpv_version_ptr;
extern MpvBuildInf mpv_build_inf;
extern unsigned char mpv_endian_mark[4]; /* 4, 3, 2, 1 */
extern int mpv_default_cond[MPV_COND_MAX];
extern MpvLib mpv_lib;
extern MpvHn *mpv_cur_hn;               /* the handle last given to MPVLIB_CheckHn */
extern char mpv_lower_work[];            /* 0x3840 bytes for the lower layer */
extern unsigned char mpv_clamp_table[1024];
extern unsigned char *mpv_clamp;        /* mpv_clamp_table + 384 */


int mpv_IsLowerReady(void);
void mpv_BuildClampTable(void);
void mpv_FinishLower(void);
void mpvlib_FreeLc(void *p, int size);
void mpvlib_AllocLc(void *p, int size);
MpvHn *mpvlib_SearchFreeHn(void);
MpvHn *mpvlib_InitHn(MpvHn *hn);
M2vObj *mpvcmc_OneMakeMbTa(MpvHn *hn);
void mpv_BindHnBuffers(MpvHn *hn);
void mpv_ResetPicInf(M2vPicAtr *inf);
void mpvcmc_BiMakeMbTa(MpvHn *hn);
void MPV_MbCbFn(void);
void mpvlib_SetCondAll(int no, int value);
void mpv_SetLowerCond(MpvHn *hn, int no, int value);
void mpv_GetLowerInf(MpvHn *hn);
int UTY_MulDiv(int a, int b, int c);

void mpv_InitLower(void);
int MPVLIB_ConvOix(int flags);
void mpvlib_ChkCacheMode(void);
void mpv_InitClampTable(unsigned char *copy);
void mpvlib_InitObjTbl(void);
void mpv_InitHw(MpvLib *pool);
void mpvlib_InitWork(int nhn, char *work);
int mpvlib_ChkFatal(void);

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
    if (MPV_CheckDelim(p) & 0x10) {
        return 0;
    }
    return 1;
}

int MPV_Init(int count, void *work) {
    int result;
    char *pool;

    mpv_version_ptr = cri_mpv_version;
    result = mpvlib_ChkFatal();
    if (result != 0) {
        if (result != 0xFF03FF05) {
            for (;;) {
            }
        }
        return result;
    }
    mpvlib_ChkCacheMode();
    mpvlib_InitWork(count, (char *)MPVLIB_ConvOix((int)work));
    pool = mpv_lib.pool;
    mpv_InitLibErr();
    mpvapi_Init();
    mpv_InitClampTable((unsigned char *)pool + 6112);
    mpvlib_InitObjTbl();
    mpv_InitHw((MpvLib *)pool);
    mpv_InitLower();
    return 0;
}

int mpvlib_ChkFatal(void) {
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

void mpvlib_ChkCacheMode(void) {
}

int MPVLIB_ConvIix(int flags) {
    if (mpv_lib.optionFlag != 0) {
        flags |= 0x02000000;
    }
    return flags;
}

int MPVLIB_ConvOix(int flags) {
    if (mpv_lib.initFlag != 0) {
        flags |= 0x02000000;
    }
    return flags;
}

/* builds the saturation table, then keeps a copy at `copy` and points mpv_clamp at the copy's centre */
void mpv_InitClampTable(unsigned char *copy) {
    mpv_BuildClampTable();
    if (copy != 0) {
        UTY_MemcpyDword(copy, mpv_clamp_table, 256);
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

void mpvlib_InitObjTbl(void) {
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
void mpvlib_InitWork(int nhn, char *work) {
    char *base;
    char *tables;
    char *pool;

    base = (char *)(((int)work + 63) & ~63);
    UTY_MemsetDword(base, 0, (nhn << 8) + 0x800);
    tables = base + (nhn << 10);
    pool = tables + 0x420;
    mpvlib_AllocLc(pool, MPV_POOL_SIZE);
    UTY_MemcpyDword(&mpv_lib, mpv_default_cond, MPV_COND_MAX);
    mpv_lib.tables = tables;
    mpv_lib.pool = pool;
    mpv_lib.nhn = nhn;
    mpv_lib.hn = (MpvHn *)base;
}

void mpv_ResetPicInf(M2vPicAtr *inf) {
    inf->horizontal_size = 0;
    inf->vertical_size = 0;
    inf->mb_width = 0;
    inf->mb_height = 0;
    inf->frame_rate_code = 0;
    inf->temporal_reference = 0;
    inf->picture_coding_type = 0;
    inf->drop_frame_flag = 0;
    inf->time_code_hours = 0;
    inf->time_code_minutes = 0;
    inf->time_code_seconds = 0;
    inf->time_code_pictures = 0;
    inf->gsc_count = 0;
    inf->shc_count = 0;
    inf->picture_structure = 3;
    inf->chroma_format = 1;
    inf->f64 = 1;
    inf->f68 = 1;
    inf->bit_rate = 0;
    inf->vbv_buffer_size = 0;
    inf->display_horizontal_size = -1;
    inf->display_vertical_size = -1;
    inf->field_count = 0;
    inf->progressive_frame = -1;
    inf->top_field_first = -1;
    inf->repeat_first_field = -1;
    inf->field_964 = 0;
    inf->aspect_ratio_information = 1;
    inf->constrained_parameters_flag = 0;
    inf->frame_rate_extension_n = 0;
    inf->frame_rate_extension_d = 0;
    inf->profile_and_level_indication = -1;
    inf->progressive_sequence = -1;
    inf->low_delay = -1;
    inf->video_format = -1;
    inf->colour_description = 0;
    inf->colour_primaries = -1;
    inf->transfer_characteristics = -1;
    inf->matrix_coefficients = -1;
}

void MPV_Finish(void) {
    mpv_FinishLower();
    mpvlib_FreeLc(mpv_lib.pool, MPV_POOL_SIZE);
}

MpvHn *MPV_Create(void) {
    MpvHn *hn;

    hn = mpvlib_SearchFreeHn();
    if (hn == 0) {
        return 0;
    }
    mpvlib_AllocLc(hn, MPV_HN_SIZE);
    hn = mpvlib_InitHn(hn);
    hn->lower = mpvcmc_OneMakeMbTa(hn);
    return hn;
}

MpvHn *mpvlib_SearchFreeHn(void) {
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

MpvHn *mpvlib_InitHn(MpvHn *hn) {
    int i;

    mpv_BindHnBuffers(hn);
    hn->f396 = 0;
    UTY_MemcpyDword(hn->cond, mpv_lib.cond, MPV_COND_MAX);
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
        MPV_SetUsrSj(hn, i, 0, 0, 0);
    }
    MPV_SetPicUsrBuf(hn, 0, 0);
    hn->stat = MPV_HN_USED;
    return hn;
}

void MPV_GetDctCnt(MpvHn *hn, int *width, int *height) {
    MpvSeqInf *seq = &hn->seq;

    *width = seq->width;
    *height = seq->height;
}

int MPV_Destroy(MpvHn *hn) {
    if (MPVLIB_CheckHn(hn) != 0) {
        return mpv_ReportError(0, 0xFF030201);
    }
    mpvcmc_BiMakeMbTa(hn);
    mpvlib_FreeLc(hn, MPV_HN_SIZE);
    hn->stat = MPV_HN_FREE;
    return 0;
}

void mpvlib_AllocLc(void *p, int size) {
}

void mpvlib_FreeLc(void *p, int size) {
}

void MPV_MbCbFn(void) {
}

/* sets condition `no` of a handle, or with no handle the default of every new and every live handle */
int MPV_SetCond(MpvHn *hn, int no, int value) {
    int *cond;

    if (no == MPV_COND_CBFN && value == 0) {
        value = (int)MPV_MbCbFn;
    }
    if (hn == 0) {
        mpvlib_SetCondAll(no, value);
        cond = mpv_lib.cond;
    } else {
        if (MPVLIB_CheckHn(hn) != 0) {
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
        if (MPVLIB_CheckHn(hn) != 0) {
            return mpv_ReportError(0, 0xFF030210);
        }
        cond = hn->cond;
    }
    *value = cond[no];
    return 0;
}

int MPVLIB_CheckHn(MpvHn *hn) {
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

M2vObj *mpvcmc_OneMakeMbTa(MpvHn *hn) {
    return mpvhook_Create();
}

void mpvcmc_BiMakeMbTa(MpvHn *hn) {
    mpvhook_Destroy(hn->lower);
}

void mpv_SetLowerCond(MpvHn *hn, int no, int value) {
    M2vObj *lower = 0;

    if (hn != 0) {
        lower = hn->lower;
    }
    mpvhook_SetCond(lower, no, (M2vCondFn)value);
}

/* hands the handle's buffers to the lower layer and starts it; -1 without a lower layer, -2 when it
 * refuses */
int mpv_StartLower(MpvHn *hn, SfdSj *sj) {
    M2vUsrSj *ent;
    int i;

    if (mpvhook_IsInstalled() != 0) {
        for (i = 0, ent = hn->bufEnt; i < 4; i++) {
            mpvhook_SetUsrSj(hn->lower, i, ent->sj, ent->fn, ent->obj);
            ent++;
        }
        mpvhook_SetPicUsrBuf(hn->lower, hn->picusr.buf, hn->picusr.size);
        if (mpvhook_DecodePicAtr(hn->lower, sj) != 0) {
            return -2;
        }
        mpvhook_GetPicUsr(hn->lower, 0, &hn->picusr.len);
        mpv_GetLowerInf(hn);
        return 0;
    }
    return -1;
}

/* matching construct: 120-order sweep of the five field stores */
void mpv_GetLowerInf(MpvHn *hn) {
    M2vPicAtr inf;
    int bitRate;
    int vbvSize, vbvDelay, reserved;
    int closedGop, brokenLink;

    mpvhook_GetPicAtr(hn->lower, &inf);
    mpvhook_GetBitRate(hn->lower, &bitRate);
    mpvhook_GetVbvBufSiz(hn->lower, &vbvSize, &vbvDelay, &reserved);
    mpvhook_GetLinkFlg(hn->lower, &closedGop, &brokenLink);
    hn->picInf = inf;
    hn->bitRate = bitRate;
    hn->vbvBufferSize = vbvSize / 2048;
    hn->vbvDelay = vbvDelay;
    hn->closedGop = closedGop;
    hn->brokenLink = brokenLink;
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
