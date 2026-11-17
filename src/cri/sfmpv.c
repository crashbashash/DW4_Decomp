#include "dw4/cri/sfmpv.h"

/* Start-code kinds: the bit MPV_CheckDelim returns for a delimiter, and the masks the searches take. */
typedef enum SfdDelim {
    SFD_DLM_SLICE = 0x02,
    SFD_DLM_PIC = 0x04,
    SFD_DLM_GOP = 0x08,
    SFD_DLM_SEQ = 0x40,
    SFD_DLM_END = 0x80
} SfdDelim;

extern char DAT_00581570[];
extern SfdMpvCond DAT_005855b0;
extern SfdMpvWorkBufs DAT_005855d8;
extern SfdMpvFrameBufs DAT_005855e0;
extern char *DAT_00585620;
extern int DAT_00585624;
extern int DAT_004beb0c;
extern int DAT_004f4e70[];
extern int DAT_00585628;
extern int DAT_004beb08;
extern int DAT_004f5060[];
extern int DAT_004f4e08[];
extern int DAT_004f4e30[];
extern int DAT_004f4e50[];

extern void *memset(void *dst, int value, unsigned int size);
extern void *memcpy(void *dst, const void *src, unsigned int size);
extern int memcmp(const void *a, const void *b, unsigned int size);
int SJRBF_GetFlowCnt(int sj, int id, int mode);
int UTY_CmpTime(int id, int arg, int a, int b);
/* matching construct: MEM_Copy (mcp.h, void) is declared returning int here; with the void
 * prototype sfmpv_SetMpvHd allocates its registers differently from retail. */
int MEM_Copy(void *dst, void *src, int n);
void UTY_MemsetDword(void *dst, int value, int size);
int MPV_CheckDelim(const unsigned char *p);
int MPV_EntryErrFunc(void *handle, void (*callback)(SfdPlayer *, int), SfdPlayer *player);
char *MPV_SearchDelim(char *data, int size, int mask);
char *MPV_BsearchDelim(char *end, int len, int mask);
void MPV_SetPicUsrBuf(void *handle, char *buf, int size);
int MPV_DecodePicAtrSj(void *handle, int sj);
int MPV_GetPicInf(void *handle, M2vPicAtr *pic);
void MPV_GetPicUsr(void *handle, char **buf, int *size);
int MPV_SkipFrmSj(void *handle, int sj);
int MPV_GetBitRate(void *handle, int *value);
void MPV_GetVbvBufSiz(void *handle, int *x, int *y, int *z);
int MPV_GetLinkFlg(void *handle, int *a, int *b);
int MPV_SetUsrSj(void *handle, int index, int a, int b, int c);
int MPV_DecodePicAtr(void *handle, void *chunk, int *result);
int MPV_Init(int count, void *work);
int MPV_Finish(void);
void *MPV_Create(void);
int MPV_Destroy();
int MPV_SetCond(void *handle, int index, int value);
int MPV_GetCond(void *handle, int index, int *value);
int UTY_MulDiv(int a, int b, int c);
long long UTY_MulDivRound64(long long a, long long b, long long c);
int SFBUF_RingGetRead(SfdPlayer *player, int index, SfdRingInfo *info);
void SFBUF_RingAddRead(SfdPlayer *player, int index, int n);
int SFBUF_GetRingBufSiz(SfdPlayer *player, int index);
int SFBUF_GetWTot(SfdPlayer *player, int index);
int SFBUF_RingGetSj(SfdPlayer *player, int index, int *entry);
void SFBUF_AddRtotSj(SfdPlayer *player, int index, int amount);
int SFBUF_SetPrepFlg(SfdPlayer *player, int index, int value);
int SFBUF_GetPrepFlg(SfdPlayer *player, int index);
int SFBUF_SetTermFlg(SfdPlayer *player, int index, int value);
int SFBUF_GetTermFlg(SfdPlayer *player, int index);
int SFBUF_RingGetDataSiz(SfdPlayer *player, int index);
void sfbuf_GetSjPos(int entry, int *a, int *b);
long sfbuf_MergeTotal(long total, int a);
void SFCON_UpdateConcatTime(SfdPlayer *player, int count);
int SFHDS_GetColType(SfdPlayer *player);
int sfd_ReportError();
int SFLIB_CheckHn(SfdPlayer *player);
void sfd_Lock(void *guard);
void sfd_Unlock(void *guard);
char *sfmpv_SearchDelim(SfdRingInfo *ring, int mask, SfdDelim *code);
char *sfmpv_BsearchDelim(SfdRingInfo *ring, int mask, SfdDelim *code);
void FUN_002a7278(SfdStream *source, int *kind, char **data, int *size);
void sfmpv_InitPicUsr(SfdBufPool *pool);
void sfmpv_SetFrmInf(SfdPlayer *player, SfdSlot *slot, SfdFrameInfo **out);
void SFMPVP_Init(void);
int SFMPVP_IsSceMpegUsed(SfdPlayer *player);
void SFMPVP_Create(SfdPlayer *player);
void FUN_002a9bc8(SfdPlayer *player);
int SFMPVP_GetFrameCount(SfdPlayer *player);
void SFPLY_AddSkipPic(SfdPlayer *player, int a, int b);
int SFPLY_GetResetFlg(void);
int SFSET_SetCond(SfdPlayer *player, int option, int value);
int SFSET_GetCond(SfdPlayer *player, int option);
void SFTIM_InitTtu(SfdTimeStamp *stamp, int value);
void SFTIM_Tc2Time(SfdTimeCode *tc, int *a, int *b);
int SFTIM_IsGetFrmTimeTunit(SfdPlayer *player, int a, int b);
int FUN_002b03e8(SfdPlayer *player, int index);

int FUN_002a3558();
int sfmpv_ChkFatal(void);
int sfmpv_ExecServerSub(SfdPlayer *player);
void sfmpv_SetCondY16(SfdPlayer *player);
void FUN_002a3850(SfdPlayer *player);
int sfmpv_GetTermDst(SfdPlayer *player);
void sfmpv_ChkPrepFlg(SfdPlayer *player);
int sfmpv_IsPrepEnd(SfdPlayer *player);
int sfmpv_IsPrepFrmEnough(SfdPlayer *player);
int sfmpv_IsVbvEnough(SfdPlayer *player);
void sfmpv_FixedStartTtu(SfdPlayer *player);
void sfmpv_ChkTermFlg(SfdPlayer *player);
void sfmpv_SetTermDst(SfdPlayer *player, int value);
int FUN_002a3c38(SfdPlayer *player);
int sfmpv_GetActiveSize(SfdPlayer *player, int *size, int *code, int *flag);
int sfmpv_DecodeOneUnit(SfdPlayer *player, int size, int code, int flag, int *done);
int sfmpv_ConcatSub(SfdPlayer *player);
int FUN_002a4958(SfdPlayer *player);
int sfmpv_CalcAudioTotTime(SfdPlayer *player);
void sfmpv_DiscardSec(SfdPlayer *player, SfdStream *stream);
void FUN_002a4b20(SfdPlayer *player, int amount);
int sfmpv_GetTermSrc(SfdPlayer *player);
int sfmpv_ChkMpvErr(SfdPlayer *player, int status, int n, int code);
void sfmpv_ReadPtsQue(SfdPlayer *player, M2vPicAtr *pic, char *pos, long *time, long *pts, int newGop);
long sfmpv_ComplementPts(SfdTimer *timer, SfdRecord *record, M2vPicAtr *pic, SfdRecordTail *entry, int newGop, long *pts);
long FUN_002a5208(int count, int rate);
void FUN_002a54d0(SfdPlayer *player, SfdSlot *slot);
void sfmpv_ReadTcode(M2vPicAtr *pic, SfdTimeCode *out);
int sfmpv_DetectTcErr(SfdPlayer *player, M2vPicAtr *pic);
void FUN_002a5740(SfdPlayer *player, M2vPicAtr *pic, long id, int flag);
void sfmpv_Pts2Tc(long pts, int prate, int drop, int tmpref, SfdTimeCode *tc);
void FUN_002a5a50(SfdTimeCode *src, SfdTimeCode *dst);
void sfmpv_SetMpvHd(SfdPlayer *player, int pts, SfdChunk *chunk);
void sfmpv_SetMvInf(SfdPicGeom *geom, int pts, M2vPicAtr *pic, int x);
int sfmpv_ChkBufSiz(SfdPlayer *player, SfdPicGeom *geom);
int sfmpv_IsDefect(SfdPlayer *player, int kind);
int sfmpv_IsPtypeSkip(SfdPlayer *player, unsigned int kind);
void sfmpv_SetSkipTtu(SfdPlayer *player);
int sfmpv_IsSeekSkip(SfdPlayer *player);
int sfmpv_IsEmptySkip(SfdPlayer *player, unsigned int type, SfdChunk *chunk);
int sfmpv_IsLate(SfdPlayer *player, unsigned int type);
void sfmpv_GetDtime(SfdPlayer *player, int unused, int *first, int *second);
void SFTIM_UpdateItime(SfdTimer *tim, int now);
int SFTIM_GetNextItime(SfdTimer *tim, int now);
int SFTIM_GetSpeed(SfdPlayer *player);
int SFTIM_GetTime(SfdPlayer *player, int *time, int *unit);
void FUN_002a6368(SfdPlayer *player, M2vPicAtr *pic, int kind);
void FUN_002a70e8(SfdPlayer *player, SfdSlot *slot);
void FUN_002a73f0(SfdChunk *dst, SfdChunk *src);
void sfmpv_RingAddRead(SfdPlayer *player, int n);
int SFBUF_GetRTot(SfdPlayer *player, int index);
int sfmpv_InitInf(SfdPlayer *player, SfdMpv *mpv);
int sfmpv_CheckMpvPara(void);
void sfmpv_InitFrmObj(SfdSlot *slot, int *ids, int count);
void sfmpv_InitPicAtr(M2vPicAtr *info);
void FUN_002a7b48(SfdPlayer *player, int code);
int sfmpv_DestroySub(void *handle);
int FUN_002a8088(SfdPlayer *player, char *body);
SfdPicRecord *FUN_002a8158(SfdPlayer *player, char *body);
int sfmpv_ReprocessShc(SfdPlayer *player, SfdMpv *mpv, int *ok);
SfdPicture *sfmpv_GetHd(SfdPlayer *player);
SfdSlot *FUN_002a8440(SfdPlayer *player, char *body);
int SFMPVF_IsTermDec(SfdPlayer *player);
int SFMPVF_GetNumFrm(SfdPlayer *player);
void SFMPVF_EndDrawFrm(SfdSlot *slot);
SfdSlot *SFMPVF_HoldFrm(SfdPlayer *player, int *out);
SfdSlot *SFMPVF_AllocFrm(SfdPlayer *player);
void SFMPVF_EndRefFrm(SfdSlot *slot);
int FUN_002a8878(SfdPlayer *player);
SfdSlot *FUN_002a8998(SfdPlayer *player);
void FUN_002a8a30(SfdPlayer *player, SfdSlot **best, SfdSlot **second);
int sfmpvf_IsChkFirst(SfdSlot *a, SfdSlot *b);
void FUN_002a75b8(SfdPlayer *player);
int sfmpv_NeedSafeDlmRefresh(SfdRingInfo *ring, SfdDelim code, char *dlm);
int sfmpv_CalcDistance(SfdRingInfo *ring, char *addr);
int sfmpv_CheckViBufSiz(SfdPlayer *player);
void SFBUF_RingGetDlm(SfdPlayer *player, int index, char **dlm, char **end);
void SFBUF_RingSetDlm(SfdPlayer *player, int index, char *dlm, char *end);
int SFMPVP_IsPscEnough(SfdPlayer *player);
int SFCON_IsEndcodeSkip(SfdPlayer *player);
int SFCON_IsVideoEndcodeSkip(SfdPlayer *player);
void SFMPVF_TermDec(SfdPlayer *player);
SfdMpv *SFMPVF_SetGopStat(SfdPlayer *player, int value);
void sfmpv_PeekChnk(SfdPlayer *player, SfdChunk *out);
void sfmpv_FixedForSeek(SfdPlayer *player);
int sfmpv_Concat(SfdPlayer *player, SfdStream *stream);
int sfmpv_IsTerm(SfdPlayer *player, int level, int kind);
int sfmpv_IsSkip(SfdPlayer *player, SfdChunk *chunk);
int sfmpv_SkipFrm(SfdPlayer *player, int sj);
int sfmpv_DecodePicAtr(SfdPlayer *player, SfdChunk *chunk, int sj, int code, int *result);
int sfmpv_DecodeFrm(SfdPlayer *player, int sj);
int sfmpv_GoDdelim(SfdPlayer *player, int unused, int mask);

void SFD_SetMpvPara(SfdMpvCond *cond) {
    DAT_005855b0 = *cond;
    DAT_005855b0.f16 = (DAT_005855b0.f16 + 0x3F) & ~0x3F;
    DAT_005855b0.f32 = (DAT_005855b0.f32 + 0x3F) & ~0x3F;
    memset(&DAT_005855d8, 0, 8);
    memset(&DAT_005855e0, 0, 0x40);
}

void SFD_SetMpvParaTbl(SfdMpvCond *cond, int *work, int *bufs)
{
    int i;
    int count;
    DAT_005855b0 = *cond;
    DAT_005855b0.f16 = 0;
    DAT_005855b0.f32 = 0;
    for (i = 0; i < 2; i++)
        DAT_005855d8.w[i] = (work[i] + 63) & ~63;
    count = cond->count;
    for (i = 0; i < 16; i++) {
        if (i < count)
            DAT_005855e0.w[i] = (bufs[i] + 63) & ~63;
        else
            DAT_005855e0.w[i] = 0;
    }
}

void SFD_MakeRfbInfo(SfdMpvCond *cond, SfdPlanes *planes) {
    int columns = (cond->f0 + 15) / 16;
    int rows;
    int lumaBlocks = (columns * 16 + 63) / 64;
    int chromaBlocks;
    char *base;
    rows = (cond->f4 + 15) / 16;
    chromaBlocks = (columns * 8 + 63) / 64;
    base = (char *)cond->f32;
    planes->lumaStride = lumaBlocks << 6;
    planes->chromaStride = chromaBlocks << 6;
    planes->base = base;
    planes->luma = base + ((lumaBlocks * rows) << 10);
    planes->chroma = planes->luma + ((chromaBlocks * rows) << 9);
}

void SFD_CalcYccPlane(char *base, int width, int height, SfdPlanes *planes) {
    int columns = (width + 15) / 16;
    int rows;
    int lumaBlocks = (columns * 16 + 63) / 64;
    int chromaBlocks;
    rows = (height + 15) / 16;
    chromaBlocks = (columns * 8 + 63) / 64;
    planes->lumaStride = lumaBlocks << 6;
    planes->chromaStride = chromaBlocks << 6;
    planes->base = base;
    planes->luma = base + ((lumaBlocks * rows) << 10);
    planes->chroma = planes->luma + ((chromaBlocks * rows) << 9);
}

void SFD_SetMpvCond(SfdPlayer *player, int mode, int value) {
    void *h = 0;
    if (player != 0) {
        SfdMpv *mpv;
        if (SFLIB_CheckHn(player) != 0) {
            sfd_ReportError(0, 0xff000181);
            return;
        }
        mpv = player->streams.hn.mpv;
        h = mpv->handle;
    }
    if (MPV_SetCond(h, mode, mode != 5 ? value : 0) != 0) {
        sfd_ReportError(player, 0xff000f12);
        return;
    }
}

int FUN_002a32b8(SfdPlayer *player, int *values, unsigned int size) {
    SfdMpv *mpv = player->streams.hn.mpv;
    void *handle = mpv->handle;
    int count;
    int i;
    if (handle == 0) {
        return 0;
    }
    count = size / 4 > 16 ? 16 : size / 4;
    for (i = 0; i < count; i++) {
        MPV_GetCond(handle, i, &values[i]);
    }
    return count;
}

void FUN_002a3340(SfdPlayer *player, int *values, int count) {
    SfdMpv *mpv;
    int *value;
    int index;
    void *handle;
    mpv = player->streams.hn.mpv;
    handle = mpv->handle;
    if (handle != 0) {
        index = 0;
        if (count > 0) {
            value = values;
            do {
                MPV_SetCond(handle, index++, *value++);
            } while (index < count);
        }
    }
}

int SFD_GetNumFrm(SfdPlayer *player, int *out) {
    *out = 0;
    if (SFLIB_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000182);
    }
    *out = SFMPVF_GetNumFrm(player);
    return 0;
}

int SFD_SetVideoUsrSj(SfdPlayer *player, int index, int a, int b, int c) {
    SfdMpv *mpv;
    if (SFLIB_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000184, a, b, c);
    }
    mpv = player->streams.hn.mpv;
    MPV_SetUsrSj(mpv->handle, index, a, b, c);
    return 0;
}

void SFD_SetPicUsrBuf(SfdPlayer *player, char *base, int count, int size) {
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000185, count, size);
        return;
    }
    FUN_002a3558(player, base);
}

int FUN_002a3558(SfdPlayer *player, char *base, int count, int size)
{
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdBufPool *pool = &mpv->pool;
    int i;
    if (base == 0 || count == 0 || size == 0) {
        sfmpv_InitPicUsr(pool);
        return 0;
    }
    if (count < player->f44 + 4)
        return sfd_ReportError(player, 0xFF000F1D);
    pool->base = base;
    i = 0;
    pool->slot[0].addr = base;
    base += size;
    pool->count = count;
    count -= 2;
    pool->slot[1].addr = base;
    base += size;
    pool->size = size;
    pool->slot[0].size = 0;
    pool->slot[1].size = 0;
    for (; i < (count < 17 ? count : 16); i++) {
        pool->slot[i + 2].size = 0;
        pool->slot[i + 2].addr = base;
        base += size;
    }
    return 0;
}

int SFMPV_Init(void) {
    int result;
    SFMPVP_Init();
    if (sfmpv_ChkFatal() != 0) {
        /* The EE short-loop workaround pads this empty loop with nops. */
        for (;;) {
        }
    }
    result = MPV_Init(8, DAT_00581570);
    if (result != 0) {
        return sfd_ReportError(0, (result == (int)0xFF03FF05) ? 0xFF000F13 : 0xFF000F01);
    }
    memset(&DAT_005855b0, 0, 36);
    memset(&DAT_005855d8, 0, 8);
    memset(&DAT_005855e0, 0, 64);
    DAT_004beb08 = 0;
    return 0;
}

int sfmpv_ChkFatal(void) {
    return 0;
}

int SFMPV_Finish(void) {
    MPV_Finish();
    return 0;
}

void SFMPV_ExecServer(SfdPlayer *player) {
    sfmpv_ExecServerSub(player);
}

int sfmpv_ExecServerSub(SfdPlayer *player) {
    int status;
    int result;
    result = SFSET_GetCond(player, 5);
    if (result != 0) {
        if (sfmpv_GetTermDst(player) == 1) {
            return 0;
        }
        sfmpv_SetCondY16(player);
        if (player->f72 == 2) {
            FUN_002a3850(player);
        }
        status = FUN_002a3c38(player);
        sfmpv_ChkPrepFlg(player);
        sfmpv_ChkTermFlg(player);
        result = status;
        return result;
    }
    return result;
}

void sfmpv_SetCondY16(SfdPlayer *player) {
    int value;
    int mode;
    if (SFSET_GetCond(player, 28) == 0) {
        return;
    }
    value = SFHDS_GetColType(player);
    if (value == 0) {
        mode = 1;
    } else if (value > 0) {
        mode = 0;
    } else if (value == -1) {
        return;
    } else {
        mode = 0;
    }
    SFD_SetMpvCond(player, 5, mode);
}

void FUN_002a3850(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.hn.mpv;
    void *handle = mpv->handle;
    int pair[2];
    int result[4];
    pair[0] = SFSET_GetCond(player, 93);
    pair[1] = SFSET_GetCond(player, 94);
    if (pair[0] != 0 && pair[1] != 0 && mpv->state == 192) {
        if (MPV_DecodePicAtr(handle, pair, result) == 0) {
            mpv->f116 = 2;
            mpv->state = 200;
        }
    }
}

int sfmpv_GetTermDst(SfdPlayer *player) {
    return SFBUF_GetTermFlg(player, player->streams.f20);
}

void sfmpv_ChkPrepFlg(SfdPlayer *player) {
    SfdStreams *streams = &player->streams;
    int target = streams->f20;
    int source = streams->f16;
    if (SFBUF_GetPrepFlg(player, target) != 1 && SFBUF_GetPrepFlg(player, source) == 1 && sfmpv_IsPrepEnd(player) != 0) {
        SFBUF_SetPrepFlg(player, target, 1);
        sfmpv_FixedStartTtu(player);
    }
}

int sfmpv_IsPrepEnd(SfdPlayer *player) {
    if ((SFMPVF_IsTermDec(player) != 0) || ((sfmpv_IsPrepFrmEnough(player) != 0) && (sfmpv_IsVbvEnough(player) != 0))) {
        return 1;
    }
    return 0;
}

int sfmpv_IsPrepFrmEnough(SfdPlayer *player) {
    int limit = player->pending.f92;
    int size = player->f44;
    if (limit == -1) {
        limit = size;
    }
    if (size < limit) {
        limit = size;
    }
    if (SFMPVF_GetNumFrm(player) < limit) {
        return 0;
    }
    return 1;
}

int sfmpv_IsVbvEnough(SfdPlayer *player)
{
    SfdMpv *mpv = player->streams.hn.mpv;
    void *handle = mpv->handle;
    SfdPicWait *wait = &player->picWait;
    int value;
    int idx;
    if (sfmpv_GetTermSrc(player) == 1)
        return 1;
    if (wait->busy != 0 && wait->f124 == 0)
        return 1;
    MPV_GetBitRate(handle, &value);
    if (value == 0x3FFFF)
        return 1;
    if (SFBUF_GetWTot(player, 1) >= mpv->limit)
        return 1;
    idx = FUN_002b03e8(player, 1) == 0;
    if (SFBUF_GetWTot(player, idx) < SFBUF_GetRingBufSiz(player, idx))
        return 0;
    return 1;
}

void sfmpv_FixedStartTtu(SfdPlayer *player) {
    SfdTimeStamp *stamp = &player->timer.f280;
    if (stamp->a != 0x7FFFFFFF) {
        stamp->done = 1;
    }
}

void sfmpv_ChkTermFlg(SfdPlayer *player) {
    SfdDecodeFlags *decode = &player->decode;
    int status = SFMPVF_GetNumFrm(player);
    if (status == -1 || (SFMPVF_IsTermDec(player) != 0 && status == 1 && decode->f24 != 0)) {
        sfmpv_SetTermDst(player, 1);
        if (decode->f0 == 0) {
            SFSET_SetCond(player, 5, 0);
        }
    }
}

void sfmpv_SetTermDst(SfdPlayer *player, int value) {
    SFBUF_SetTermFlg(player, player->streams.f20, value);
}

int FUN_002a3c38(SfdPlayer *player) {
    int a;
    int b;
    int c;
    int more;
    int status;
    do {
        status = sfmpv_GetActiveSize(player, &a, &b, &c);
        if (status != 0) {
            break;
        }
        status = sfmpv_DecodeOneUnit(player, a, b, c, &more);
        if (status != 0) {
            break;
        }
    } while (more != 0);
    FUN_002a75b8(player);
    return status;
}

/* Sizes the unit at the video ring's read position: *size bytes up to the next start code, *code the
 * kind of the start code at the read position, and *flag set when the read position holds no start code. */
int sfmpv_GetActiveSize(SfdPlayer *player, int *size, int *code, int *flag) {
    SfdRingInfo inf;
    int bufin = player->streams.f16;
    char *p;
    SfdDelim dcode;
    char *dlm;
    char *dlmend;
    char *end;
    SfdDelim found;
    int ret;
    int n;

    *size = 0;
    *code = 0;
    *flag = 0;
    ret = SFBUF_RingGetRead(player, bufin, &inf);
    if (ret != 0)
        return ret;
    if (inf.len0 == 0)
        return 0;
    p = sfmpv_SearchDelim(&inf, SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC | SFD_DLM_SLICE, &dcode);
    if (p != inf.addr0) {
        if (p != 0) {
            *size = sfmpv_CalcDistance(&inf, p);
        } else {
            n = inf.len0 + inf.len1 - 3;
            *size = (n < 0) ? 0 : n;
        }
        if (*size > 0)
            *flag = 1;
        return 0;
    }
    *size = 4;
    *code = dcode;
    if (dcode & SFD_DLM_END)
        return 0;
    SFBUF_RingGetDlm(player, bufin, &dlm, &dlmend);
    if (sfmpv_NeedSafeDlmRefresh(&inf, dcode, dlm)) {
        dlm = 0;
        if (inf.len1 == 0)
            end = inf.addr0 + inf.len0;
        else
            end = inf.addr1 + inf.len1;
        if (dlmend != end) {
            dlmend = end;
            p = sfmpv_BsearchDelim(&inf, SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC, &found);
            dlm = p;
            SFBUF_RingSetDlm(player, bufin, p, dlmend);
        }
    }
    if (dlm == 0)
        return sfmpv_CheckViBufSiz(player);
    found = MPV_CheckDelim((unsigned char *)dlm);
    switch ((int)found) {
    case SFD_DLM_GOP:
        if (dcode & SFD_DLM_SEQ) {
            p = sfmpv_SearchDelim(&inf, SFD_DLM_GOP, &dcode);
            if (p == 0 || p == dlm)
                return sfmpv_CheckViBufSiz(player);
        }
        break;
    case SFD_DLM_PIC:
        if (dcode & (SFD_DLM_SEQ | SFD_DLM_GOP)) {
            p = sfmpv_SearchDelim(&inf, SFD_DLM_PIC, &dcode);
            if (p == 0 || p == dlm)
                return sfmpv_CheckViBufSiz(player);
        }
        break;
    case SFD_DLM_SEQ:
    case SFD_DLM_END:
    default:
        break;
    }
    *size = sfmpv_CalcDistance(&inf, dlm);
    return 0;
}

/* Whether the delimiter the ring remembers is no longer a safe next start code (1) or still is (0). */
int sfmpv_NeedSafeDlmRefresh(SfdRingInfo *ring, SfdDelim code, char *dlm) {
    char tmp[4];
    int n;
    char *p;

    if (dlm == 0)
        return 1;
    if (dlm == ring->addr0)
        return 1;
    if (dlm > ring->addr0) {
        if (dlm - ring->addr0 < 4)
            return 1;
    }
    if (dlm >= ring->addr0 && dlm < ring->addr0 + ring->len0) {
        n = dlm + 4 - (ring->addr0 + ring->len0);
        if (n > 0) {
            if (n > ring->len1)
                return 1;
            memcpy(tmp, dlm, 4 - n);
            memcpy(tmp + 4 - n, ring->addr1, n);
        } else {
            memcpy(tmp, dlm, 4);
        }
    } else if (dlm >= ring->addr1 && dlm < ring->addr1 + ring->len1) {
        n = dlm + 4 - (ring->addr1 + ring->len1);
        if (n > 0)
            return 1;
        memcpy(tmp, dlm, 4);
    } else {
        return 1;
    }
    switch (MPV_CheckDelim((unsigned char *)tmp)) {
    case SFD_DLM_SEQ:
    case SFD_DLM_END:
        break;
    case SFD_DLM_GOP:
        if ((code & SFD_DLM_SEQ) == 0)
            break;
        p = sfmpv_SearchDelim(ring, SFD_DLM_GOP, &code);
        if (p == 0 || p == dlm)
            return 1;
        break;
    case SFD_DLM_PIC:
        if ((code & (SFD_DLM_SEQ | SFD_DLM_GOP)) == 0)
            break;
        p = sfmpv_SearchDelim(ring, SFD_DLM_PIC, &code);
        if (p == 0 || p == dlm)
            return 1;
        break;
    default:
        return 1;
    }
    return 0;
}

int sfmpv_CalcDistance(SfdRingInfo *ring, char *addr) {
    int offset;
    if (addr >= ring->addr0 && addr < ring->addr0 + ring->len0) {
        offset = addr - ring->addr0;
    } else if (addr >= ring->addr1 && addr < ring->addr1 + ring->len1) {
        offset = addr - ring->addr1 + ring->len0;
    } else {
        offset = 0;
    }
    return offset;
}

int sfmpv_CheckViBufSiz(SfdPlayer *player) {
    int index = player->streams.f16;
    int total = SFBUF_GetRingBufSiz(player, index);
    if (total - SFBUF_RingGetDataSiz(player, index) < player->f40) {
        return sfd_ReportError(player, 0xFF000F1C);
    }
    return 0;
}

/* Searches the readable data of the ring (two chunks) for a start code in `mask`, including one that
 * straddles the wrap; returns its address and its kind in *code, or 0. */
char *sfmpv_SearchDelim(SfdRingInfo *ring, int mask, SfdDelim *code) {
    char tmp[8];
    char *p;
    int n1;
    int n2;
    int i;
    int c;

    *code = 0;
    p = MPV_SearchDelim(ring->addr0, ring->len0, mask);
    if (p != 0) {
        *code = MPV_CheckDelim(p);
        return p;
    }
    if (ring->len1 == 0) {
        return 0;
    }
    n1 = (ring->len0 < 3) ? ring->len0 : 3;
    n2 = (ring->len1 < 3) ? ring->len1 : 3;
    memcpy(tmp, ring->addr0 + ring->len0 - n1, n1);
    memcpy(tmp + n1, ring->addr1, n2);
    for (i = 0; i < n1 + n2 - 3; i++) {
        c = MPV_CheckDelim(&tmp[i]);
        if (c & mask) {
            *code = c;
            return ring->addr0 + ring->len0 - n1 + i;
        }
    }
    p = MPV_SearchDelim(ring->addr1, ring->len1, mask);
    if (p != 0) {
        *code = MPV_CheckDelim(p);
        return p;
    }
    return 0;
}

/* The same search backwards from the end of the readable data. */
char *sfmpv_BsearchDelim(SfdRingInfo *ring, int mask, SfdDelim *code) {
    char tmp[8];
    char *p;
    int n1;
    int n2;
    int i;
    int c;

    *code = 0;
    if (ring->len1 != 0) {
        p = MPV_BsearchDelim(ring->addr1 + ring->len1, ring->len1, mask);
        if (p != 0) {
            *code = MPV_CheckDelim(p);
            return p;
        }
        n1 = (ring->len0 < 3) ? ring->len0 : 3;
        n2 = (ring->len1 < 3) ? ring->len1 : 3;
        memcpy(tmp, ring->addr0 + ring->len0 - n1, n1);
        memcpy(tmp + n1, ring->addr1, n2);
        for (i = 0; i < n1 + n2 - 3; i++) {
            c = MPV_CheckDelim(&tmp[i]);
            if (c & mask) {
                *code = c;
                return ring->addr0 + ring->len0 - n1 + i;
            }
        }
    }
    p = MPV_BsearchDelim(ring->addr0 + ring->len0, ring->len0, mask);
    if (p != 0) {
        *code = MPV_CheckDelim(p);
        return p;
    }
    return 0;
}

/* Decodes the start-code-delimited unit at the read position. */
int sfmpv_DecodeOneUnit(SfdPlayer *player, int size, int code, int flag, int *done) {
    SfdDecodeFlags *decode = &player->decode;
    SfdStreams *streams;
    SfdMpv *mpv;
    int bufin;
    int ret;
    int sj;
    int result;
    int picResult;
    SfdChunk chunk;

    *done = 0;
    streams = &player->streams;
    bufin = streams->f16;
    mpv = streams->hn.mpv;
    decode->f36 = 0;
    if (SFMPVP_IsPscEnough(player) == 0) {
        if (sfmpv_GetTermSrc(player) == 1) {
            SFMPVF_TermDec(player);
            return 0;
        }
        decode->f36 = 1;
        return sfmpv_CheckViBufSiz(player);
    }
    if (mpv->state != (SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC) || mpv->f368 == 0) {
        code &= SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC;
    }
    ret = SFBUF_RingGetSj(player, bufin, &sj);
    if (ret != 0) {
        return 0;
    }
    if (sj == 0) {
        return ret;
    }
    if (code & (SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP)) {
        SFMPVF_SetGopStat(player, 1);
    }
    if (code == SFD_DLM_END) {
        sfmpv_FixedForSeek(player);
    }
    if (code == SFD_DLM_END && SFCON_IsEndcodeSkip(player) != 0) {
        if (sfmpv_Concat(player, (SfdStream *)sj) == 0) {
            *done = 1;
        }
    } else if (code == SFD_DLM_END && SFCON_IsVideoEndcodeSkip(player) != 0) {
        sfmpv_DiscardSec(player, (SfdStream *)sj);
        *done = 1;
    } else if (flag == 0 && sfmpv_IsTerm(player, size, code)) {
        SFMPVF_TermDec(player);
    } else if (flag == 0 && size <= 4) {
        decode->f36 = 1;
    } else if (code & (SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC)) {
        sfmpv_PeekChnk(player, &chunk);
        ret = sfmpv_DecodePicAtr(player, &chunk, sj, code, &result);
        if (ret != 0) {
            return ret;
        }
        /* held in a local: read from result, it is reloaded after the mpv stores below */
        picResult = result;
        if (picResult == 0) {
            if (code & mpv->state) {
                mpv->state = SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC;
            }
            mpv->f368 = 1;
        }
        if (code == SFD_DLM_SEQ && picResult == -2) {
            mpv->state = SFD_DLM_END | SFD_DLM_SEQ;
        }
        *done = 1;
    } else if (code & SFD_DLM_SLICE) {
        sfmpv_PeekChnk(player, &chunk);
        if (sfmpv_IsSkip(player, &chunk)) {
            ret = sfmpv_SkipFrm(player, sj);
            if (ret == 0) {
                *done = 1;
            }
        } else {
            ret = sfmpv_DecodeFrm(player, sj);
        }
    } else if (code != SFD_DLM_END) {
        if (sfmpv_GoDdelim(player, sj, SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC) > 0) {
            *done = 1;
        }
    }
    return ret;
}

void sfmpv_PeekChnk(SfdPlayer *player, SfdChunk *out) {
    SfdRingInfo info;
    if (SFBUF_RingGetRead(player, player->streams.f16, &info) != 0) {
        out->addr = 0;
        out->size = 0;
    } else {
        out->addr = info.addr0;
        out->size = info.len0;
    }
}

void sfmpv_FixedForSeek(SfdPlayer *player) {
    SfdTimeStamp *stamp = &player->timer.f148;
    SfdStreams *streams = &player->streams;
    int index = streams->f16;
    if (streams->f32 < 0) streams->f32 = SFBUF_GetRTot(player, index) + 4;
    if (stamp->a < 0) *stamp = player->timer.best;
}

int sfmpv_Concat(SfdPlayer *player, SfdStream *stream) {
    if (sfmpv_ConcatSub(player) == -1) {
        return -1;
    }
    sfmpv_DiscardSec(player, stream);
    return 0;
}

int sfmpv_ConcatSub(SfdPlayer *player) {
    SfdTimer *timer = &player->timer;
    SfdMpv *mpv = player->streams.hn.mpv;
    int count;
    if (SFSET_GetCond(player, 6) == 0) {
        count = FUN_002a4958(player);
    } else {
        count = sfmpv_CalcAudioTotTime(player);
        if (count < 0) {
            return -1;
        }
    }
    if (count > 0) {
        SFCON_UpdateConcatTime(player, count);
        mpv->f136++;
        if (SFMPVP_IsSceMpegUsed(player) != 0) {
            timer->f352 = SFMPVP_GetFrameCount(player) + 1;
        }
    }
    SFTIM_InitTtu(&timer->state, 0x7FFFFFFF);
    SFTIM_InitTtu(&timer->best, -1);
    mpv->state = 192;
    return 0;
}

int FUN_002a4958(SfdPlayer *player) {
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int position;
    int size;
    /* matching construct: manual — best.done/best.tc read through the player, state.a through the state pointer */
    if (player->timer.best.done == 0) {
        return 0;
    }
    FUN_002a5a50(&player->timer.best.tc, &tc);
    tc.add = 0;
    SFTIM_Tc2Time(&tc, &position, &size);
    return position - state->a;
}

void sfmpv_DiscardSec(SfdPlayer *player, SfdStream *stream) {
    int buf[4];
    for (;;) {
        stream->ops->read(stream, 1, 4, buf);
        if (buf[1] != 4 || MPV_CheckDelim((const unsigned char *)buf[0]) != 128) {
            break;
        }
        stream->ops->skip(stream, 0, buf);
        FUN_002a4b20(player, 4);
    }
    stream->ops->end(stream, 1, buf);
}

void FUN_002a4b20(SfdPlayer *player, int amount) {
    SFBUF_AddRtotSj(player, player->streams.f16, amount);
    player->f2464 += amount;
}

int sfmpv_IsTerm(SfdPlayer *player, int level, int kind) {
    if (kind == 128) {
        return 1;
    }
    if (level < 5 && sfmpv_GetTermSrc(player) == 1) {
        return 1;
    }
    return 0;
}

int sfmpv_GetTermSrc(SfdPlayer *player) {
    return SFBUF_GetTermFlg(player, player->streams.f16);
}

int sfmpv_ChkMpvErr(SfdPlayer *player, int status, int n, int code)
{
    switch (status) {
    case 0:
        return 0;
    case -2:
        if (n > 0)
            return 0;
        return sfd_ReportError(player, status);
    case -3:
        if (n > 0)
            return 0;
        return sfd_ReportError(player, status);
    default:
        return sfd_ReportError(player, code);
    }
}

/* decodes the picture header at the delimiter: the picture user data, a size change, the reference
 * order of the picture, the new group of pictures and the picture's time stamp */
int sfmpv_DecodePicAtr(SfdPlayer *player, SfdChunk *chunk, int sj, int code, int *result) {
    SfdMpv *mpv = player->streams.hn.mpv;
    void *handle = mpv->handle;
    M2vPicAtr *pic = &mpv->pic;
    SfdBufPool *pool = &mpv->pool;
    long time;
    long pts;
    int before;
    int moved;
    int err;
    int seq;
    int last;
    char *pos;
    int (*seqFn)(void *obj, int width, int height);
    void *seqObj;
    void (*hdrFn)(void *obj, char *data, int size);
    void *hdrObj;

    pool->slot[0].size = 0;
    MPV_SetPicUsrBuf(handle, pool->slot[0].addr, pool->size);
    before = SJRBF_GetFlowCnt(sj, 0, 1);
    *result = MPV_DecodePicAtrSj(handle, sj);
    moved = SJRBF_GetFlowCnt(sj, 0, 1) - before;
    err = sfmpv_ChkMpvErr(player, *result, moved, 0xFF000F04);
    FUN_002a4b20(player, moved);
    if (err != 0) {
        return err;
    }
    if (*result == -2) {
        return 0;
    }
    *result = MPV_GetPicInf(handle, pic);
    if (*result != 0) {
        return sfd_ReportError(player, 0xFF000F05);
    }
    seq = code & 0x40;
    if (seq) {
        if (player->geom.width > 0
            && (player->geom.width != pic->horizontal_size || player->geom.height != pic->vertical_size)) {
            *result = -2;
            return 0;
        }
        seqFn = (int (*)(void *, int, int))SFSET_GetCond(player, 95);
        seqObj = (void *)SFSET_GetCond(player, 95);
        if (seqFn != 0 && seqFn(seqObj, pic->horizontal_size, pic->vertical_size) != 0) {
            *result = -2;
            return 0;
        }
    }
    if (pic->picture_coding_type == 1) {
        mpv->f372 = 0;
    } else if (player->bufFmt == 3 && mpv->second != 0) {
        last = mpv->second->info.temporal_reference;
        if (pic->picture_coding_type == 2) {
            if (pic->temporal_reference < last && last < 512) {
                mpv->f372 = 1;
            }
        } else if (pic->picture_coding_type == 3) {
            if (pic->temporal_reference >= last) {
                mpv->f372 = 1;
            }
        }
    }
    MPV_GetPicUsr(handle, 0, &pool->slot[0].size);
    if (mpv->f268 != pic->gsc_count) {
        mpv->f268 = pic->gsc_count;
        mpv->f272 = 1;
    } else {
        mpv->f272 = 0;
    }
    if (seq) {
        hdrFn = (void (*)(void *, char *, int))SFSET_GetCond(player, 77);
        hdrObj = (void *)SFSET_GetCond(player, 78);
        if (hdrFn != 0) {
            pos = MPV_SearchDelim(chunk->addr, chunk->size, 1);
            if (pos != 0) {
                hdrFn(hdrObj, chunk->addr, pos + 4 - chunk->addr);
            }
        }
    }
    pos = MPV_SearchDelim(chunk->addr, chunk->size, 4);
    sfmpv_ReadPtsQue(player, pic, pos, &time, &pts, mpv->f272);
    mpv->f4256 = pts;
    if ((code & mpv->state) == 0) {
        return 0;
    }
    sfmpv_CalcRepeatField(player, pic, mpv->f272);
    sfmpv_ReformTc(player, pic, time, mpv->f272);
    FUN_002a5b48(player, pic);
    FUN_002a5c28(player, pic);
    return sfmpv_FirstPicAtr(player, handle, pic, chunk);
}

void sfmpv_InitComplementPts(SfdRecord *record) {
    SfdRecordTail *tail = &record->tail;
    record->f0 = 0;
    record->f4 = 0;
    record->f8 = 0;
    tail->f0 = -1;
    tail->f12 = -1;
    tail->f8 = 0;
}

long sfmpv_ComplementPts(SfdTimer *timer, SfdRecord *record, M2vPicAtr *pic, SfdRecordTail *entry, int newGop, long *pts) {
    int rate = DAT_004f5060[pic->frame_rate_code];
    int number = pic->temporal_reference;
    long origin;
    long time;
    int distance;

    if (timer->f336 < 0) {
        origin = entry->f0 - FUN_002a5208(number, rate);
        if (origin < 0) {
            origin = 0;
        }
        timer->f336 = origin;
    }
    time = entry->f0 - timer->f336;
    if (time < 0) {
        time = 0;
    }
    if (memcmp(&record->tail, entry, 4) != 0) {
        int type = pic->picture_coding_type;

        record->tail = *entry;
        record->f0 = number;
        record->f4 = 0;
        if (type == 3) {
            record->f8 = 1;
        } else {
            record->f8 = 0;
        }
        *pts = entry->f0;
    } else {
        if (newGop) {
            record->f4 += record->f8 + 1;
            record->f8 = 0;
            record->f0 = 0;
        }
        distance = number - record->f0;
        record->f8 = (record->f8 > distance) ? record->f8 : distance;
        time += FUN_002a5208(record->f4 + distance, rate);
        if (time < 0) {
            time = 0;
        }
    }
    return time;
}

long FUN_002a5208(int count, int rate) {
    return (long)count * 90000000 / rate;
}

/* repeat_first_field accounting: the field offset of each picture of the group, kept by temporal reference */
void sfmpv_CalcRepeatField(SfdPlayer *player, M2vPicAtr *pic, int newGop) {
    SfdTimer *timer = &player->timer;
    SfdFieldEntry *fields = timer->fields;
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdSlot *ref;
    int i;
    int idx;
    int t;
    int last;
    int cur;
    int j;

    sfmpv_ReadTcode(pic, &timer->tc);
    if (newGop != 0) {
        for (i = 0; i < 64; i++) {
            fields[i].f0 = -1;
        }
        fields[0].f2 = -1;
    } else if (pic->picture_coding_type == 1 || pic->picture_coding_type == 2) {
        ref = mpv->second;
        cur = pic->temporal_reference;
        last = ref->info.temporal_reference;
        if (cur < last) {
            cur += 1024;
        }
        for (t = last + 1; t < cur; t++) {
            fields[t % 64].f0 = -1;
        }
    }
    idx = pic->temporal_reference % 64;
    fields[idx].f0 = timer->tc.field0;
    if (newGop != 0) {
        fields[idx].f2 = 0;
    } else if (pic->temporal_reference == 0 && (short)fields[0].f2 == -1) {
        fields[0].f2 = 0;
    } else {
        for (i = 0; i < 64; i++) {
            j = (idx - i + 63) % 64;
            if (fields[j].f0 != -1) {
                fields[idx].f2 = fields[j].f0 + fields[j].f2;
                break;
            }
        }
    }
    timer->tc.field = fields[idx].f2;
    if (pic->picture_coding_type == 3 && fields[idx].f0 != 0) {
        j = mpv->second->info.temporal_reference % 64;
        fields[j].f2 = fields[idx].f0 + fields[idx].f2;
        mpv->second->stamp.tc.field = fields[j].f2;
        FUN_002a54d0(player, mpv->second);
        FUN_002a70e8(player, mpv->second);
    }
}

void FUN_002a54d0(SfdPlayer *player, SfdSlot *slot) {
    int t[2];
    SfdTimer *timer;
    int d;
    timer = &player->timer;
    SFTIM_Tc2Time(&slot->stamp.tc, &t[0], &t[1]);
    d = t[0] - timer->state.a;
    slot->stamp.done = 1;
    slot->stamp.a = d;
    slot->stamp.b = t[1];
    if (d >= timer->best.a) {
        timer->best = slot->stamp;
    }
}

void sfmpv_ReformTc(SfdPlayer *player, M2vPicAtr *pic, long a, int b) {
    int enabled = SFSET_GetCond(player, 52);
    if (enabled == 0) {
        if (a >= 0 || pic->gsc_count == 0 || pic->repeat_first_field != 0
            || (b != 0 && sfmpv_DetectTcErr(player, pic) != 0)) {
            enabled = 1;
            SFSET_SetCond(player, 52, 1);
        }
    }
    if (enabled == 1) {
        FUN_002a5740(player, pic, a, b);
    }
}

int sfmpv_DetectTcErr(SfdPlayer *player, M2vPicAtr *pic) {
    SfdTimeCode tc;
    int now;
    int rate;
    int start;
    int span;
    if (player->timer.best.done == 0) {
        return 0;
    }
    tc = player->timer.tc;
    SFTIM_Tc2Time(&tc, &now, &rate);
    SFTIM_Tc2Time(&player->timer.best.tc, &start, &rate);
    span = SFSET_GetCond(player, 53) * rate;
    if (now <= start) {
        return 1;
    }
    if (now < start + span) {
        return 0;
    }
    return 1;
}

void FUN_002a5740(SfdPlayer *player, M2vPicAtr *pic, long id, int flag)
{
    SfdTimer *timer = &player->timer;
    int b = pic->drop_frame_flag;
    int a = pic->frame_rate_code;
    int idx = pic->temporal_reference;
    if (flag != 0 && id >= 0) {
        sfmpv_Pts2Tc(id, a, b, idx, &player->timer.tc);
        return;
    }
    if (timer->best.done == 0) {
        if (player->userWork == 0) {
            timer->tc.rate = a;
            timer->tc.drop = 0;
            timer->tc.hour = 0;
            timer->tc.minute = 0;
            timer->tc.second = 0;
            timer->tc.frame = 0;
        }
    } else if (flag != 0) {
        FUN_002a5a50(&timer->best.tc, &timer->tc);
        timer->fields[0].f2 = timer->tc.field;
        timer->fields[idx].f2 = timer->tc.field;
    } else {
        timer->tc.rate = timer->best.tc.rate;
        timer->tc.drop = timer->best.tc.drop;
        timer->tc.hour = timer->best.tc.hour;
        timer->tc.minute = timer->best.tc.minute;
        timer->tc.second = timer->best.tc.second;
        timer->tc.frame = timer->best.tc.frame;
    }
}

void sfmpv_Pts2Tc(long pts, int prate, int drop, int tmpref, SfdTimeCode *tc)
{
    int rnd = DAT_004f4e08[prate];
    int rate = DAT_004f5060[prate];
    const int *tbl;
    int fno;
    int hour;
    int ten;
    int min;
    int sec;
    int frm;
    int sec_tot;
    int min_tot;

    fno = UTY_MulDivRound64(pts, rate * 2, 90000000);
    tc->field = fno & 1;
    fno >>= 1;
    fno -= tmpref;
    fno = (fno > 0) ? fno : 0;
    tc->rate = prate;
    tc->drop = drop;
    if (drop != 0 && (rate == 29970 || rate == 59940)) {
        tbl = (rate == 29970) ? DAT_004f4e30 : DAT_004f4e50;
        hour = fno / tbl[0];
        fno = fno % tbl[0];
        ten = fno / tbl[1];
        fno = fno % tbl[1];
        if (fno < tbl[2]) {
            min = 0;
            sec = fno / tbl[5];
            frm = fno % tbl[5];
        } else {
            fno -= tbl[2];
            min = fno / tbl[3] + 1;
            fno = fno % tbl[3];
            if (fno < tbl[4]) {
                sec = 0;
                frm = fno + tbl[7];
            } else {
                fno -= tbl[4];
                sec = fno / tbl[5] + 1;
                frm = fno % tbl[5];
            }
        }
        min += tbl[6] * ten;
    } else {
        sec_tot = fno / rnd;
        frm = fno % rnd;
        min_tot = sec_tot / 60;
        sec = sec_tot % 60;
        hour = min_tot / 60;
        min = min_tot % 60;
    }
    tc->hour = hour;
    tc->minute = min;
    tc->second = sec;
    tc->frame = frm;
}

void FUN_002a5b48(SfdPlayer *player, M2vPicAtr *pic)
{
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int a, b;
    if (state->done != 0)
        return;
    tc = player->timer.tc;
    tc.add = 0;
    SFTIM_Tc2Time(&tc, &a, &b);
    state->tc = tc;
    state->a = a;
    state->b = b;
    state->done = 1;
}

void FUN_002a5c28(SfdPlayer *player, M2vPicAtr *pic)
{
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int a, b;
    SfdTimeStamp *cur;
    SfdTimeStamp *best;
    int d;
    tc = player->timer.tc;
    SFTIM_Tc2Time(&tc, &a, &b);
    player->timer.cur.tc = tc;
    cur = &player->timer.cur;
    best = &player->timer.best;
    d = a - state->a;
    cur->done = 1;
    cur->a = d;
    cur->b = b;
    if (d >= best->a)
        *best = *cur;
}

void sfmpv_ReadTcode(M2vPicAtr *pic, SfdTimeCode *out) {
    out->rate = pic->frame_rate_code;
    out->drop = pic->drop_frame_flag;
    out->hour = pic->time_code_hours;
    out->minute = pic->time_code_minutes;
    out->second = pic->time_code_seconds;
    out->frame = pic->time_code_pictures;
    out->add = pic->temporal_reference;
    out->field0 = (signed char)pic->field_count;
    out->field = 0;
}

int sfmpv_FirstPicAtr(SfdPlayer *player, void *sj, M2vPicAtr *pic, SfdChunk *chunk)
{
    SfdPicGeom *geom = &player->geom;
    SfdMpv *mpv = player->streams.hn.mpv;
    int pts;
    int x, y, z;
    int n;
    if (geom->f16 != 0)
        return 0;
    if (MPV_GetBitRate(sj, &pts) != 0)
        return sfd_ReportError(player, 0xFF000F16);
    MPV_GetVbvBufSiz(sj, &x, &y, &z);
    if (SFSET_GetCond(player, 60) == 0)
        mpv->limit = 0;
    else {
        n = SFBUF_GetRingBufSiz(player, 1);
        if (z == -1)
            z = x;
        mpv->limit = z < n ? z : n;
    }
    sfmpv_SetMpvHd(player, pts, chunk);
    sfmpv_SetMvInf(geom, pts, pic, x);
    return sfmpv_ChkBufSiz(player, geom);
}

void sfmpv_SetMpvHd(SfdPlayer *player, int pts, SfdChunk *chunk)
{
    SfdPicture *picture;
    SfdUserData *user;
    int len;
    SfdTimer *timer;
    picture = sfmpv_GetHd(player);
    if (picture == 0 || picture->valid != 0)
        return;
    len = chunk->size;
    user = &picture->user;
    if (len > 512)
        len = 512;
    timer = &player->timer;
    user->size = len;
    MEM_Copy(user->data, chunk->addr, len);
    if (pts == 0x3FFFF) {
        picture->pts = 0;
        picture->hasPts = 0;
    } else {
        picture->hasPts = 1;
        picture->pts = pts * 50;
    }
    picture->stamp = timer->state;
    picture->valid = 1;
}

void sfmpv_SetMvInf(SfdPicGeom *geom, int pts, M2vPicAtr *pic, int x) {
    /* matching construct: statement-order sweep — pic->frame_rate_code is read before the copies */
    int fifth = pic->frame_rate_code;
    geom->width = pic->horizontal_size;
    geom->height = pic->vertical_size;
    geom->f8 = pic->mb_width;
    geom->f12 = pic->mb_height;
    geom->f20 = fifth;
    geom->f16 = pts;
    geom->f32 = x;
}

/* The pictures must fit the frame size the decoder was set up for, and its frame buffers must hold a
 * picture: a macroblock takes 1024 bytes as ARGB8888 output (format 2), 384 as YCC 4:2:0. */
int sfmpv_ChkBufSiz(SfdPlayer *player, SfdPicGeom *geom) {
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdMpvCond *cond = &mpv->cond;
    int fmt = player->bufFmt;
    int count = cond->count;
    unsigned int frmsize;
    int buf;
    int i;
    int mbw, mbh;
    int bufmbw, bufmbh;

    if (cond->f8 * cond->f12 < geom->width * geom->height)
        return sfd_ReportError(player, 0xFF000F17);
    mbw = geom->width / 16;
    mbh = geom->height / 16;
    frmsize = (fmt == 2 ? mbw * mbh * 1024 : mbw * mbh * 384) + 64;
    bufmbw = cond->f20 / 16;
    bufmbh = cond->f24 / 16;
    if ((fmt == 2 ? bufmbw * bufmbh * 1024 : bufmbw * bufmbh * 384) + 64 < frmsize)
        return sfd_ReportError(player, 0xFF000F18);
    buf = cond->f32;
    if (buf != 0) {
        for (i = 0; i < count; i++) {
            mpv->bufs.w[i] = buf + i * frmsize;
        }
    } else {
        for (i = 0; i < count; i++) {
        }
    }
    mpv->slotCount = count;
    sfmpv_InitFrmObj(mpv->slots, mpv->bufs.w, count);
    return 0;
}

int sfmpv_IsConcatTimeFix(SfdPlayer *player) {
    return player->timer.base >= 0;
}

int sfmpv_IsSkip(SfdPlayer *player, SfdChunk *chunk) {
    SfdMpv *mpv = player->streams.hn.mpv;
    M2vPicAtr *pic = &mpv->pic;
    int skip;
    int busy;
    unsigned int type;
    if (SFSET_GetCond(player, 47) == 1)
        return 1;
    if (SFSET_GetCond(player, 39) == 1)
        return 0;
    if (pic->field_964 != 0)
        return mpv->f364;
    type = pic->picture_coding_type;
    busy = sfmpv_IsSeekSkip(player);
    skip = 1;
    if (busy == 0 && sfmpv_IsPtypeSkip(player, type) == 0 && sfmpv_IsEmptySkip(player, type, chunk) == 0
        && sfmpv_IsDefect(player, type) == 0)
        skip = sfmpv_IsLate(player, type) != 0;
    FUN_002a6368(player, pic, skip);
    return skip;
}

int sfmpv_IsDefect(SfdPlayer *player, int kind) {
    SfdMpv *mpv = player->streams.hn.mpv;
    unsigned int mode = mpv->f116;
    int result = 0;
    switch (mode) {
    case 4: /* matching construct: manual — explicit empty case shapes the compare tree */
        break;
    case 2:
        if ((unsigned int)(kind - 2) < 2) {
            result = 1;
        }
        break;
    case 3:
        result = kind == mode;
        break;
    }
    return result;
}

void FUN_002a6368(SfdPlayer *player, M2vPicAtr *pic, int kind)
{
    SfdMpv *mpv = player->streams.hn.mpv;
    void *handle = mpv->handle;
    int mode = mpv->f116;
    int a, b;
    if (mpv->f272 != 0) {
        MPV_GetLinkFlg(handle, &a, &b);
        if (a == 1)
            mode = 5;
        else {
            if (player->timer.f280.done == 0 && SFSET_GetCond(player, 73) == 1)
                b = 1;
            if (b == 1)
                mode = 2;
        }
    }
    if (kind == 1) {
        if (pic->picture_coding_type == 1 || pic->picture_coding_type == 2)
            mode = 2;
    } else if (mode == 2)
        mode = 3;
    else if (mode == 3)
        mode = 5;
    mpv->f116 = mode;
}

int sfmpv_IsSeekSkip(SfdPlayer *player) {
    SfdLink *link = &player->link;
    SfdTimeStamp *cur = &player->timer.cur;
    SfdTimeStamp *f280 = &player->timer.f280;
    if (link->id < 0) {
        return 0;
    }
    if (f280->done != 0) {
        return 0;
    }
    return UTY_CmpTime(link->id, link->arg, cur->a, cur->b) == 0;
}

int sfmpv_IsPtypeSkip(SfdPlayer *player, unsigned int kind) {
    SfdPending *pending = &player->pending;
    int value;
    switch (kind) {
    case 1:
        value = pending->f8;
        break;
    case 2:
        value = pending->f12;
        break;
    case 3:
        value = pending->f16;
        break;
    default:
        return 1;
    }
    return value == 0;
}

int MPV_IsEmptyBpic(unsigned char *buf, int nbyte, int nmb);
int MPV_IsEmptyPpic(unsigned char *buf, int nbyte, int nmb);

int sfmpv_IsEmptySkip(SfdPlayer *player, unsigned int type, SfdChunk *chunk) {
    SfdDecodeFlags *dec;
    SfdPicGeom *geom;
    int r;

    if (SFSET_GetCond(player, 7) != 0) {
        return 0;
    }
    geom = &player->geom;
    dec = &player->decode;
    if (type == 3) {
        r = MPV_IsEmptyBpic((unsigned char *)chunk->addr, chunk->size, geom->f8 * geom->f12);
        if (r != 0) {
            dec->f16++;
        }
    } else if (type == 2) {
        r = MPV_IsEmptyPpic((unsigned char *)chunk->addr, chunk->size, geom->f8 * geom->f12);
        if (r != 0) {
            dec->f20++;
        }
    } else {
        r = 0;
    }
    return r;
}

/* Whether the picture would be shown late: the timer's skip hook decides when one is set, otherwise
 * its display time against the current time, within the allowed number of skips. */
int sfmpv_IsLate(SfdPlayer *player, unsigned int type) {
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdTimer *timer = &player->timer;
    SfdTimeStamp *cur = &timer->cur;
    SfdTimeStamp *ofs = &timer->f280;
    int time;
    int unit;
    int now;
    int nowUnit;
    int dnum;
    int dden;

    if (ofs->done == 0) {
        time = 0;
    } else {
        time = cur->a - ofs->a + timer->base;
    }
    unit = cur->b;
    if (timer->hook != 0) {
        return timer->hook(player, type, time, unit);
    }
    if (type == 1) {
        SFTIM_UpdateItime(timer, time);
    }
    if (type == 1 || type == 2) {
        time = SFTIM_GetNextItime(timer, time);
    }
    if (SFTIM_GetSpeed(player) <= 1000 && mpv->f132 >= player->pending.f152) {
        return 0;
    }
    SFTIM_GetTime(player, &now, &nowUnit);
    if (now < 0) {
        return 0;
    }
    sfmpv_GetDtime(player, type, &dnum, &dden);
    time = time - unit * dnum / dden;
    if (UTY_CmpTime(now, nowUnit, time, unit) != 0) {
        return 0;
    }
    mpv->f132++;
    return 1;
}

void sfmpv_GetDtime(SfdPlayer *player, int unused, int *first, int *second) {
    SfdPending *pending = &player->pending;
    *second = pending->f172;
    *first = pending->f168;
}

int sfmpv_SkipFrm(SfdPlayer *player, int sj)
{
    SfdMpv *mpv = player->streams.hn.mpv;
    void *handle = mpv->handle;
    M2vPicAtr *pic;
    int before;
    int status;
    int used;
    int ret;
    sfmpv_SetSkipTtu(player);
    before = SJRBF_GetFlowCnt(sj, 0, 1);
    pic = &mpv->pic;
    status = MPV_SkipFrmSj(handle, sj);
    used = SJRBF_GetFlowCnt(sj, 0, 1) - before;
    ret = sfmpv_ChkMpvErr(player, status, used, 0xFF000F07);
    FUN_002a4b20(player, used);
    if (ret != 0)
        return ret;
    if (pic->field_964 == 0)
        mpv->f364 = 1;
    SFPLY_AddSkipPic(player, 1, pic->picture_coding_type);
    return 0;
}

void sfmpv_SetSkipTtu(SfdPlayer *player) {
    SfdTimeStamp *current = &player->timer.cur;
    SfdTimeStamp *latest = &player->timer.latest;
    if (current->a < player->timer.f280.a) {
        *latest = *current;
    }
}

/* takes the frame the picture is decoded into and the reference planes it predicts from */
int sfmpv_SetFrmPara(SfdPlayer *player, M2vPicAtr *pic, SfdFrmPara *para, SfdSlot **out) {
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdDecodeFlags *decode = &player->decode;
    SfdPlanes *planes;
    int columns;
    int rows;
    int lumaBlocks;
    int chromaBlocks;
    int lumaSize;
    int chromaSize;

    if (mpv->f360 != 0) {
        *out = mpv->f360;
    } else {
        *out = SFMPVF_AllocFrm(player);
        if (*out == 0) {
            decode->f40 = 1;
            return -1;
        }
    }
    (*out)->info = *pic;
    (*out)->f216 = mpv->f4256;
    if (player->bufFmt == 3) {
        if ((pic->picture_coding_type == 1 || pic->picture_coding_type == 2) && mpv->f360 == 0) {
            SFMPVF_EndRefFrm(mpv->first);
            mpv->first = mpv->second;
            mpv->second = *out;
        }
        columns = (pic->horizontal_size + 15) / 16;
        lumaBlocks = (columns * 16 + 63) / 64;
        rows = (pic->vertical_size + 15) / 16;
        chromaBlocks = (columns * 8 + 63) / 64;
        lumaSize = (lumaBlocks * rows) << 10;
        chromaSize = (chromaBlocks * rows) << 9;
        para->ref[0].lumaStride = lumaBlocks << 6;
        para->ref[0].chromaStride = chromaBlocks << 6;
        para->ref[0].base = mpv->first->buf;
        para->ref[0].luma = para->ref[0].base + lumaSize;
        para->ref[0].chroma = para->ref[0].luma + chromaSize;
        para->ref[1].lumaStride = lumaBlocks << 6;
        para->ref[1].chromaStride = chromaBlocks << 6;
        para->ref[1].base = mpv->second->buf;
        para->ref[1].luma = para->ref[1].base + lumaSize;
        para->ref[1].chroma = para->ref[1].luma + chromaSize;
    } else {
        if (pic->picture_coding_type == 1 || pic->picture_coding_type == 2) {
            mpv->f312 ^= 1;
            mpv->f316 ^= 1;
            mpv->second = *out;
        }
        planes = mpv->planes;
        para->ref[0] = planes[mpv->f312];
        para->ref[1] = planes[mpv->f316];
    }
    para->dst = (*out)->buf;
    para->pic = &(*out)->info;
    para->nfrm = 0;
    para->nbyte = 0;
    decode->f40 = 0;
    return 0;
}

void FUN_002a6ea0(SfdPlayer *player, SfdMpv *mpv, int *out64, int *out68) {
    if (player->bufFmt == 3) {
        switch (mpv->pic.picture_coding_type) {
        case 1: /* matching construct: manual — explicit single-layer case shapes the compare tree */
            break;
        case 2:
            *out64 = mpv->first->f64;
            *out68 = mpv->first->f68;
            return;
        case 3:
            *out64 = mpv->first->f64 + mpv->second->f64;
            *out68 = mpv->first->f68 + mpv->second->f68;
            return;
        }
    }
    *out64 = 0;
    *out68 = 0;
}

void sfmpv_SetStartTtu(SfdPlayer *player)
{
    SfdTimeStamp *state2 = &player->timer.f280;
    SfdTimeStamp *state = &player->timer.state;
    SfdTimeCode tc;
    int a, b;
    if (state2->done != 0)
        return;
    tc = player->timer.cur.tc;
    if (sfmpv_IsDefect(player, 3) == 0 && sfmpv_IsPtypeSkip(player, 3) == 0)
        tc.add = 0;
    SFTIM_Tc2Time(&tc, &a, &b);
    state2->tc = tc;
    state2->a = a - state->a;
    state2->b = b;
    state2->done = 1;
}

void FUN_002a7040(SfdPlayer *player, SfdSlot *slot) {
    slot->stamp = player->timer.cur;
    if (SFMPVP_IsSceMpegUsed(player) != 0) {
        slot->f224 = SFMPVP_GetFrameCount(player);
    }
    FUN_002a70e8(player, slot);
}

void FUN_002a70e8(SfdPlayer *player, SfdSlot *slot) {
    SfdTimer *timer = &player->timer;
    SfdTimeStamp *in = &slot->stamp;
    int t;
    slot->f60 = in->b;
    slot->f56 = in->a - player->timer.f280.a + timer->base;
    slot->f76 = in->a;
    slot->f80 = in->a + timer->base;
    if (SFMPVP_IsSceMpegUsed(player) != 0) {
        t = UTY_MulDiv(slot->f60, (slot->f224 - timer->f352) * 1000, DAT_004f5060[slot->info.frame_rate_code]);
        slot->f76 = t;
        slot->f56 = slot->f80 = t + timer->base;
    }
    if (timer->f644 < slot->f56) {
        timer->f644 = slot->f56;
        timer->f648 = slot->f60;
    }
}

void FUN_002a71d0(SfdPlayer *player, SfdSlot *slot, void *source) {
    SfdMpv *mpv = player->streams.hn.mpv;
    int kind;
    char *data;
    int size;
    if ((unsigned int)(slot->info.picture_coding_type - 1) < 2) {
        FUN_002a73f0(&mpv->pool.slot[1], slot->blob);
    }
    FUN_002a7278(source, &kind, &data, &size);
    if (kind == 3) {
        memcpy(slot->blob->addr, data, size);
        slot->blob->size = size;
    } else {
        FUN_002a73f0(slot->blob, &mpv->pool.slot[1]);
    }
}

void FUN_002a7278(SfdStream *source, int *kind, char **data, int *size) {
    SfdChunk chunk;
    char *seq;
    char *pic;
    char *ext;
    int rest;

    *kind = 0;
    *data = 0;
    *size = 0;
    source->ops->read(source, 1, 0x7FFFFFFF, (int *)&chunk);
    seq = MPV_SearchDelim(chunk.addr, chunk.size, 204);
    if (seq == 0) {
        DAT_004beb0c++;
    } else {
        if ((MPV_CheckDelim(seq) & 4) != 0) {
            if (chunk.size < seq - chunk.addr + 6) {
                DAT_004beb0c++;
            } else {
                *kind = DAT_004f4e70[(seq[5] >> 3) & 7];
                if (*kind == 3) {
                    rest = chunk.addr - seq + chunk.size;
                    pic = MPV_SearchDelim(seq, rest, 34);
                    if (pic != 0 && (MPV_CheckDelim(pic) & 0x20) != 0) {
                        ext = MPV_SearchDelim(seq, rest, 2);
                        if (ext == 0) {
                            DAT_004beb0c++;
                        } else {
                            *data = pic;
                            *size = ext - pic;
                        }
                    }
                }
            }
        }
    }
    source->ops->end(source, 1, (int *)&chunk);
}

void FUN_002a73f0(SfdChunk *dst, SfdChunk *src) {
    memcpy(dst->addr, src->addr, src->size);
    dst->size = src->size;
}

int sfmpv_GoDdelim(SfdPlayer *player, int unused, int mask)
{
    SfdRingInfo area;
    SfdDelim code;
    char *p;
    int n;
    int i;
    int found;
    int c;
    if (SFBUF_RingGetRead(player, player->streams.f16, &area) != 0)
        return 0;
    if (area.len0 == 0)
        return 0;
    p = sfmpv_SearchDelim(&area, mask, &code);
    if (p == 0) {
        n = area.len0 + area.len1 - 3;
        if (n < 0)
            n = 0;
    } else if (p >= area.addr0 && p < area.addr0 + area.len0)
        n = p - area.addr0;
    else if (p >= area.addr1 && p < area.addr1 + area.len1)
        n = p - area.addr1 + area.len0;
    else
        n = 0;
    sfmpv_RingAddRead(player, n);
    found = 0;
    for (i = 0; i < (n < 4 ? n : 3); i++) {
        if (i < area.len0)
            c = area.addr0[i];
        else
            c = area.addr1[i - area.len0];
        if (c != 0) {
            found = 1;
            break;
        }
    }
    if (found)
        player->f2472 += n;
    player->f2464 += n;
    return n;
}

/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void sfmpv_RingAddRead(SfdPlayer *player, int n)
{
    SFBUF_RingAddRead(player, player->streams.f16, n);
    EMPTY_MACRO();
}

void FUN_002a75b8(SfdPlayer *player) {
    int entry;
    int a;
    int b;
    SFBUF_RingGetSj(player, player->streams.f16, &entry);
    if (entry != 0) {
        sfbuf_GetSjPos(entry, &a, &b);
        player->f2456 = sfbuf_MergeTotal(player->f2456, a);
    }
}

int SFMPV_Create(SfdPlayer *player)
{
    SfdMpv *mpv = &player->mpvBody;
    void *dec;
    int ret;
    ret = SFSET_GetCond(player, 5);
    if (ret == 0)
        return ret;
    player->streams.hn.mpv = mpv;
    ret = sfmpv_InitInf(player, mpv);
    if (ret != 0)
        return ret;
    SFMPVP_Create(player);
    dec = MPV_Create();
    if (dec == 0)
        return sfd_ReportError(0, 0xFF000F0A);
    if (MPV_EntryErrFunc(dec, FUN_002a7b48, player) != 0) {
        sfmpv_DestroySub(dec);
        return sfd_ReportError(0, 0xFF000F0B);
    }
    MPV_SetCond(dec, 1, SFSET_GetCond(player, 0));
    MPV_SetCond(dec, 2, SFSET_GetCond(player, 1));
    MPV_SetCond(dec, 6, player->bufFmt);
    mpv->handle = dec;
    if (SFPLY_GetResetFlg() != 0)
        FUN_002a3558(player, DAT_00585620, DAT_00585624, DAT_00585628);
    return 0;
}

int sfmpv_InitInf(SfdPlayer *player, SfdMpv *mpv) {
    int i;

    if (sfmpv_CheckMpvPara() != 0) {
        return sfd_ReportError(0, 0xFF000F15);
    }
    mpv->cond = DAT_005855b0;
    mpv->work = DAT_005855d8;
    mpv->bufs = DAT_005855e0;
    mpv->f116 = 5;
    mpv->state = 192;
    mpv->f316 = 1;
    mpv->handle = 0;
    mpv->current = 0;
    mpv->f312 = 0;
    mpv->f124 = 0;
    mpv->f128 = 0;
    mpv->first = 0;
    mpv->second = 0;
    mpv->f360 = 0;
    mpv->f364 = 0;
    mpv->f368 = 0;
    mpv->f372 = 0;
    sfmpv_InitFrmObj(mpv->slots, mpv->bufs.w, 16);
    mpv->f132 = 0;
    mpv->f136 = 0;
    sfmpv_InitPicAtr(&mpv->pic);
    mpv->f268 = -1;
    mpv->f272 = 0;
    mpv->limit = 0x7FFFFFFF;
    sfmpv_InitComplementPts((SfdRecord *)&mpv->track);
    sfmpv_InitPicUsr(&mpv->pool);
    for (i = 15; i >= 0; i--) {
        mpv->slots[i].blob = &mpv->pool.slot[i + 2];
    }
    return 0;
}

int sfmpv_CheckMpvPara(void) {
    int i;
    if ((unsigned)(DAT_005855b0.count - 1) >= 16) {
fail:
        return -1;
    }
    if (DAT_005855b0.f16 == 0 || DAT_005855b0.f32 == 0) {
        for (i = 0; i < 2; i++) {
            if (DAT_005855d8.w[i] == 0) goto fail;
        }
        for (i = 0; i < DAT_005855b0.count; i++) {
            if (DAT_005855e0.w[i] == 0) goto fail;
        }
    }
    return 0;
}

void sfmpv_InitFrmObj(SfdSlot *slot, int *ids, int count) {
    if (count > 0) {
        int *id = ids;
        int remaining = count;
        do {
            slot->state = 0;
            slot->refs = 0;
            SFTIM_InitTtu(&slot->stamp, 0);
            slot->buf = (void *)*id++;
            slot->f56 = 0;
            slot->f60 = 1;
            slot->f64 = 0;
            slot->f68 = 0;
            slot->f72 = 0;
            slot->f76 = 0;
            slot->f80 = 0;
            sfmpv_InitPicAtr(&slot->info);
            slot->f224 = 0;
            slot++;
        } while (--remaining != 0);
    }
}

void sfmpv_InitPicAtr(M2vPicAtr *info) {
    UTY_MemsetDword(info, -1, 32);
}

void sfmpv_InitPicUsr(SfdBufPool *pool) {
    int i;
    pool->base = 0;
    pool->count = 0;
    pool->size = 0;
    pool->slot[0].addr = 0;
    pool->slot[0].size = 0;
    pool->slot[1].addr = 0;
    pool->slot[1].size = 0;
    for (i = 0; i < 16; i++) {
        pool->slot[i + 2].addr = 0;
        pool->slot[i + 2].size = 0;
    }
}

void FUN_002a7b48(SfdPlayer *player, int code) {
    if (code < -3 || (code >= -1 && code != 0)) {
        sfd_ReportError(player, code);
    }
}

int FUN_002a7b88(SfdPlayer *player)
{
    SfdMpv *mpv = player->streams.hn.mpv;
    void *dec = mpv->handle;
    if (dec == 0)
        return 0;
    DAT_005855b0 = mpv->cond;
    DAT_005855d8 = mpv->work;
    DAT_005855e0 = mpv->bufs;
    DAT_00585620 = mpv->pool.base;
    DAT_00585624 = mpv->pool.count;
    DAT_00585628 = mpv->pool.size;
    FUN_002a9bc8(player);
    if (sfmpv_DestroySub(dec) != 0)
        return sfd_ReportError(player, 0xFF000F0C);
    mpv->handle = 0;
    return 0;
}

int sfmpv_DestroySub(void *handle) {
    return MPV_Destroy(handle);
}

int SFMPV_Standby(void) {
    return 0;
}

int SFMPV_Start(void) {
    return 0;
}

int SFMPV_Stop(void) {
    return 0;
}

int SFMPV_Pause(void) {
    return 0;
}

void SFMPV_GetWrite(SfdPlayer *player) {
    sfd_ReportError(player, 0xFF000F0D);
}

void SFMPV_AddWrite(SfdPlayer *player) {
    sfd_ReportError(player, 0xFF000F0D);
}

int SFMPV_GetRead(SfdPlayer *player, SfdFrameInfo **out) {
    int buf[4];
    SfdTimer *timer = &player->timer;
    SfdSlot *slot;
    if (SFMPVF_GetNumFrm(player) == -1) {
        *out = 0;
        return 0;
    }
    slot = SFMPVF_HoldFrm(player, buf);
    if (slot == 0) {
        *out = 0;
        return 0;
    }
    sfmpv_SetFrmInf(player, slot, out);
    timer->f636 = (*out)->f20;
    timer->f640 = (*out)->f24;
    return 0;
}

/* matching construct: placement — declared here; with the other declarations it changes the
 * address-taken local loads of FUN_002a5c28 */
SfdPicRecord *FUN_002a8488(SfdPlayer *player, SfdSlot *target);

/* fills the frame information handed to the application from the frame's slot and marks its record
 * in use */
void sfmpv_SetFrmInf(SfdPlayer *player, SfdSlot *slot, SfdFrameInfo **out) {
    SfdMpv *mpv = player->streams.hn.mpv;
    M2vPicAtr *pic = &slot->info;
    SfdPicRecord *record;

    record = FUN_002a8488(player, slot);
    *out = (SfdFrameInfo *)record->body;
    record->f0 = 1;
    mpv->current = slot;
    (*out)->f0 = pic->horizontal_size;
    (*out)->f4 = pic->vertical_size;
    (*out)->f8 = pic->mb_width;
    (*out)->f12 = pic->mb_height;
    (*out)->picType = pic->picture_coding_type;
    (*out)->f20 = slot->f56;
    (*out)->f24 = slot->f60;
    (*out)->bufFmt = player->bufFmt;
    (*out)->buf = slot->buf;
    (*out)->f36 = slot->f64;
    (*out)->f40 = slot->f68;
    (*out)->f44 = slot->f72;
    (*out)->f48 = slot->f76;
    (*out)->f52 = slot->f80;
    (*out)->picUsr = slot->blob;
    (*out)->f60 = pic->f64;
    (*out)->f64 = pic->f68;
    if (pic->f64 == 0) {
        (*out)->tail.detail.f72 = 2;
    } else {
        (*out)->tail.detail.f72 = 1;
    }
    (*out)->tail.detail.f80 = slot->f216;
    (*out)->tail.detail.f88 = pic->picture_structure;
    (*out)->tail.detail.f92 = pic->chroma_format;
    (*out)->tail.detail.f96 = pic->bit_rate;
    (*out)->tail.detail.f100 = pic->vbv_buffer_size;
    (*out)->tail.detail.f104 = pic->display_horizontal_size;
    (*out)->tail.detail.f106 = pic->display_vertical_size;
    (*out)->tail.detail.f108 = pic->progressive_frame;
    (*out)->tail.detail.f109 = pic->top_field_first;
    (*out)->tail.detail.f110 = pic->repeat_first_field;
    (*out)->tail.detail.f111 = pic->aspect_ratio_information;
    (*out)->tail.detail.f112 = pic->constrained_parameters_flag;
    (*out)->tail.detail.f113 = pic->frame_rate_extension_n;
    (*out)->tail.detail.f114 = pic->frame_rate_extension_d;
    (*out)->tail.detail.f115 = pic->profile_and_level_indication;
    (*out)->tail.detail.f116 = pic->progressive_sequence;
    (*out)->tail.detail.f117 = pic->low_delay;
    (*out)->tail.detail.f118 = pic->video_format;
    (*out)->tail.detail.f119 = pic->colour_description;
    (*out)->tail.detail.f120 = pic->colour_primaries;
    (*out)->tail.detail.f121 = pic->transfer_characteristics;
    (*out)->tail.detail.f122 = pic->matrix_coefficients;
}

int SFMPV_AddRead(SfdPlayer *player, char *body) {
    char guard[16];
    int result;
    sfd_Lock(guard);
    result = FUN_002a8088(player, body);
    sfd_Unlock(guard);
    return result;
}

int FUN_002a8088(SfdPlayer *player, char *body) {
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdPicRecord *record = FUN_002a8158(player, body);
    SfdSlot *found;
    SfdSlot *current;
    if (record->f0 != 1) {
        return sfd_ReportError(player, 0xFF000F0E);
    }
    found = FUN_002a8440(player, body);
    current = mpv->current;
    if (current != found) {
        return sfd_ReportError(player, 0xFF000F0F);
    }
    record->f0 = 0;
    SFMPVF_EndDrawFrm(current);
    return 0;
}

SfdPicRecord *FUN_002a8158(SfdPlayer *player, char *body) {
    return (SfdPicRecord *)(body - 8);
}

int SFMPV_Seek(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.hn.mpv;
    int flag[4];
    int ready;
    int status;
    status = sfmpv_ReprocessShc(player, mpv, flag);
    if (status != 0) {
        return status;
    }
    ready = flag[0];
    mpv->f116 = 2;
    if (ready == 0 || SFSET_GetCond(player, 48) == 0) {
        mpv->state = 192;
    } else {
        mpv->state = 200;
    }
    return 0;
}

int sfmpv_ReprocessShc(SfdPlayer *player, SfdMpv *mpv, int *ok)
{
    SfdPicture *picture;
    SfdChunk chunk;
    SfdUserData *user;
    int out[4];
    *ok = 0;
    picture = sfmpv_GetHd(player);
    if (picture == 0)
        return 0;
    if (picture->valid == 0)
        return 0;
    player->timer.state = picture->stamp;
    user = &picture->user;
    chunk.addr = user->data;
    chunk.size = user->size;
    if (MPV_DecodePicAtr(mpv->handle, &chunk, out) != 0)
        return sfd_ReportError(player, 0xFF000F1B);
    *ok = 1;
    return 0;
}

SfdPicture *sfmpv_GetHd(SfdPlayer *player) {
    char *work = player->userWork;
    SfdMpv *mpv = player->streams.hn.mpv;
    if (work == 0) {
        return 0;
    }
    if (mpv->f136 > 0) {
        return 0;
    }
    return (SfdPicture *)(work + 2768);
}

void FUN_002a82f8(SfdPlayer *player, char *body) {
    SfdSlot *slot;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000188);
        return;
    }
    slot = FUN_002a8440(player, body);
    if (slot == 0) {
        sfd_ReportError(player, 0xFF000F30);
    } else {
        slot->refs++;
    }
    player->decode.f44++;
}

void FUN_002a8398(SfdPlayer *player, char *body) {
    SfdSlot *slot;
    int count;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000189);
    } else {
        slot = FUN_002a8440(player, body);
        if (slot == 0) {
            sfd_ReportError(player, 0xFF000F31);
        } else {
            count = slot->refs - 1;
            slot->refs = count < 0 ? 0 : count;
        }
        player->decode.f44--;
    }
}

SfdSlot *FUN_002a8440(SfdPlayer *player, char *body) {
    SfdPicRecord *record = player->records;
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdSlot *slot = mpv->slots;
    int i;
    for (i = 0; i < 16; i++) {
        if (record->body == body) {
            return slot;
        }
        record++;
        slot++;
    }
    return 0;
}

SfdPicRecord *FUN_002a8488(SfdPlayer *player, SfdSlot *target) {
    SfdMpv *mpv = player->streams.hn.mpv;
    int i = 0;
    int count = mpv->slotCount;
    SfdSlot *slot = mpv->slots;
    SfdPicRecord *record;
    if (count > 0) {
        record = player->records;
        do {
            /* matching construct: hand — the candidate is taken before the
               advance, so the compare sits in the copy's delay slot */
            SfdPicRecord *found = record;
            record++;
            if (slot == target) {
                return found;
            }
            i++;
            slot++;
        } while (i < count);
    }
    return 0;
}

void SFMPVF_TermDec(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.hn.mpv;
    mpv->f124 = 1;
}

int SFMPVF_IsTermDec(SfdPlayer *player) {
    SfdMpv *mpv = player->streams.hn.mpv;
    return mpv->f124;
}

SfdMpv *SFMPVF_SetGopStat(SfdPlayer *player, int value) {
    SfdMpv *mpv = player->streams.hn.mpv;
    mpv->f128 = value;
    return mpv;
}

int SFMPVF_GetNumFrm(SfdPlayer *player) {
    char guard[16];
    SfdMpv *mpv;
    SfdSlot *slot;
    int count;
    int i;
    int n;
    sfd_Lock(guard);
    mpv = player->streams.hn.mpv;
    count = 0;
    slot = mpv->slots;
    n = mpv->slotCount;
    for (i = 0; i < n; i++) {
        if (slot->state == 2 || slot->state == 4) {
            count++;
        }
        slot++;
    }
    if (mpv->f124 == 1 && count == 0) {
        count = -1;
    }
    sfd_Unlock(guard);
    return count;
}

SfdSlot *SFMPVF_AllocFrm(SfdPlayer *player) {
    char guard[16];
    SfdMpv *mpv;
    SfdSlot *slot;
    int i;
    int n;
    sfd_Lock(guard);
    mpv = player->streams.hn.mpv;
    n = mpv->slotCount;
    slot = mpv->slots;
    for (i = 0; i < n; i++, slot++) {
        if (*(long *)slot == 0) {
            slot->state = 1;
            break;
        }
    }
    if (i == n) {
        slot = 0;
    }
    sfd_Unlock(guard);
    return slot;
}

void SFMPVF_FreeFrm(SfdSlot *slot) {
    if (slot != 0) {
        slot->state = 0;
    }
}

void SFMPVF_StbyFrm(SfdSlot *slot) {
    if (slot != 0) {
        slot->state = 2;
    }
}

void SFMPVF_RefStbyFrm(SfdSlot *slot) {
    if (slot != 0) {
        slot->state = 4;
    }
}

void SFMPVF_EndDrawFrm(SfdSlot *slot) {
    if (slot != 0) {
        if (slot->state == 4) {
            slot->state = 3;
        } else {
            slot->state = 0;
        }
    }
}

void SFMPVF_EndRefFrm(SfdSlot *slot) {
    if (slot != 0) {
        if (slot->state == 4) {
            slot->state = 2;
        } else {
            slot->state = 0;
        }
    }
}

SfdSlot *SFMPVF_HoldFrm(SfdPlayer *player, int *out) {
    int c;
    SfdSlot *best = 0;
    int n = 0;
    SfdMpv *mpv;
    SfdSlot *slot;
    int i, cnt;
    sfd_Lock(&c);
    mpv = player->streams.hn.mpv;
    cnt = mpv->slotCount;
    slot = mpv->slots;
    *out = 0;
    for (i = 0; i < cnt; i++, slot++) {
        if (slot->state == 2 || slot->state == 4) {
            if (sfmpvf_IsChkFirst(best, slot) != 0) best = slot;
            n++;
        }
    }
    if (n == 1 && mpv->f124 != 0) *out = n;
    sfd_Unlock(&c);
    return best;
}

void SFD_GetNextPicUsr(SfdPlayer *player, char **data, int *size) {
    SfdSlot *slot = FUN_002a8998(player);
    SfdChunk *chunk;
    if (slot == 0) {
        *data = 0;
        *size = 0;
        return;
    }
    chunk = slot->blob;
    if (chunk == 0) {
        *data = 0;
        *size = 0;
        return;
    }
    *data = chunk->addr;
    *size = chunk->size;
}

int SFD_GetNumRemainFrm(SfdPlayer *player) {
    int refused;
    int count;
    refused = SFLIB_CheckHn(player);
    if (refused != 0) {
        sfd_ReportError(0, 0xFF000187);
        return 0;
    }
    count = FUN_002a8878(player);
    if (player->decode.f24 == 1 && count > 0) {
        count--;
    }
    return count;
}

int FUN_002a8878(SfdPlayer *player) {
    int c;
    SfdSlot *p, *q;
    int k, r;
    sfd_Lock(&c);
    FUN_002a8a30(player, &p, &q);
    if (player->f72 != 4) q = 0;
    k = SFSET_GetCond(player, 15);
    if (p != 0 && (k == 0 || SFTIM_IsGetFrmTimeTunit(player, p->f56, p->f60) != 0)) {
        if (q != 0 && (k == 0 || SFTIM_IsGetFrmTimeTunit(player, q->f56, q->f60) != 0)) {
            r = 2;
        } else {
            r = 1;
        }
    } else {
        r = 0;
    }
    sfd_Unlock(&c);
    return r;
}

int SFD_IsNextFrmReady(SfdPlayer *player) {
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000183);
        return 0;
    }
    return FUN_002a8998(player) != 0;
}

SfdSlot *FUN_002a8998(SfdPlayer *player) {
    int guard;
    SfdSlot *best;
    SfdSlot *second;
    sfd_Lock(&guard);
    if (player->f72 != 4) {
        second = 0;
    } else {
        FUN_002a8a30(player, &best, &second);
        if (second != 0 && SFSET_GetCond(player, 15) != 0) {
            if (SFTIM_IsGetFrmTimeTunit(player, second->f56, second->f60) == 0) {
                second = 0;
            }
        }
    }
    sfd_Unlock(&guard);
    return second;
}

void FUN_002a8a30(SfdPlayer *player, SfdSlot **best, SfdSlot **second) {
    SfdMpv *mpv;
    SfdSlot *slot;
    int held = 0;
    int i;
    int n;
    mpv = player->streams.hn.mpv;
    *best = 0;
    *second = 0;
    n = mpv->slotCount;
    slot = mpv->slots;
    for (i = 0; i < n; i++) {
        if (slot->state == 2 || slot->state == 4) {
            held++;
            if (sfmpvf_IsChkFirst(*best, slot) != 0) {
                *second = *best;
                *best = slot;
            } else if (sfmpvf_IsChkFirst(*second, slot) != 0) {
                *second = slot;
            }
        }
        slot++;
    }
    if (held <= 0) {
        *best = 0;
        *second = 0;
    } else if (held == 1) {
        *second = 0;
    }
}

int sfmpvf_IsChkFirst(SfdSlot *a, SfdSlot *b) {
    int result;
    result = 1;
    if (a != 0) {
        result = a->f56 > b->f56;
    }
    return result;
}
