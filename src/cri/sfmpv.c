#include "dw4/cri/sfmpv.h"
#include "dw4/cri/mpv.h"
#include <string.h>
#include "dw4/cri/mps.h"
#include "dw4/cri/uty.h"
#include "dw4/cri/sfd.h"

/* Start-code kinds: the bit MPV_CheckDelim returns for a delimiter, and the masks the searches take. */
typedef enum SfdDelim {
    SFD_DLM_SLICE = 0x02,
    SFD_DLM_PIC = 0x04,
    SFD_DLM_GOP = 0x08,
    SFD_DLM_SEQ = 0x40,
    SFD_DLM_END = 0x80
} SfdDelim;

extern char sfmpv_work[];
extern SfdMpvCond sfmpv_para;
extern SfdMpvWorkBufs sfmpv_rfb_adr_tbl;
extern SfdMpvFrameBufs sfmpv_ta_adr_tbl;
extern char *sfmpv_picusr_pbuf;
extern int sfmpv_picusr_bufnum;
extern int DAT_004beb0c;
extern int DAT_004f4e70[];
extern int sfmpv_picusr_buf1siz;
extern int sfmpv_discard_wsiz;
extern int sfmpv_fps_round[];
extern int sfmpv_conv_29_97[];
extern int sfmpv_conv_59_94[];

/* kept here: the <string.h> prototype changes the code emitted for the memcmp call in sfmpv_ComplementPts */
extern int memcmp(const void *a, const void *b, unsigned int size);
/* matching construct: MEM_Copy (mcp.h, void) is declared returning int here; with the void
 * prototype sfmpv_SetMpvHd allocates its registers differently from retail. */
int MEM_Copy(void *dst, void *src, int n);
int MPV_EntryErrFunc(void *handle, void (*callback)(SfdPlayer *, int), SfdPlayer *player);
char *sfmpv_SearchDelim(SfdRingInfo *ring, int mask, SfdDelim *code);
char *sfmpv_BsearchDelim(SfdRingInfo *ring, int mask, SfdDelim *code);
void FUN_002a7278(SfdStream *source, int *kind, char **data, int *size);
void sfmpv_InitPicUsr(SfdBufPool *pool);
void sfmpv_SetFrmInf(SfdPlayer *player, SfdSlot *slot, SfdFrameInfo **out);

int sfmpv_SetPicUsrBuf(SfdPlayer *player, char *base, int count, int size);
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
int sfmpv_DecodeSomePic(SfdPlayer *player);
int sfmpv_GetActiveSize(SfdPlayer *player, int *size, int *code, int *flag);
int sfmpv_DecodeOneUnit(SfdPlayer *player, int size, int code, int flag, int *done);
int sfmpv_ConcatSub(SfdPlayer *player);
int sfmpv_CalcVideoTotTime(SfdPlayer *player);
int sfmpv_CalcAudioTotTime(SfdPlayer *player);
void sfmpv_DiscardSec(SfdPlayer *player, SfdStream *stream);
void sfmpv_AddRtotSj(SfdPlayer *player, int amount);
int sfmpv_GetTermSrc(SfdPlayer *player);
int sfmpv_ChkMpvErr(SfdPlayer *player, int status, int n, int code);
void sfmpv_ReadPtsQue(SfdPlayer *player, M2vPicAtr *pic, char *pos, long long *time, long long *pts, int newGop);
long long sfmpv_ComplementPts(SfdTim *timer, SfdRecord *record, M2vPicAtr *pic, SfdRecordTail *entry, int newGop, long long *pts);
long long sfmpv_Nfrm2Pts(int count, int rate);
void FUN_002a54d0(SfdPlayer *player, SfdSlot *slot);
void sfmpv_ReadTcode(M2vPicAtr *pic, SfdTimeCode *out);
int sfmpv_DetectTcErr(SfdPlayer *player, M2vPicAtr *pic);
void sfmpv_DoReformTc(SfdPlayer *player, M2vPicAtr *pic, long long id, int flag);
void sfmpv_Pts2Tc(long long pts, int prate, int drop, int tmpref, SfdTimeCode *tc);
void sfmpv_NextTc(SfdTimeCode *src, SfdTimeCode *dst);
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
void sfmpv_UpdateDefect(SfdPlayer *player, M2vPicAtr *pic, int kind);
void sfmpv_SetFrmTime(SfdPlayer *player, SfdSlot *slot);
void FUN_002a73f0(SfdChunk *dst, SfdChunk *src);
void sfmpv_RingAddRead(SfdPlayer *player, int n);
int sfmpv_InitInf(SfdPlayer *player, SfdMpv *mpv);
int sfmpv_CheckMpvPara(void);
void sfmpv_InitFrmObj(SfdSlot *slot, int *ids, int count);
void sfmpv_InitPicAtr(M2vPicAtr *info);
void sfmpv_ErrFn(SfdPlayer *player, int code);
int sfmpv_DestroySub(void *handle);
int sfmpv_AddReadSub(SfdPlayer *player, char *body);
SfdPicRecord *FUN_002a8158(SfdPlayer *player, char *body);
int sfmpv_ReprocessShc(SfdPlayer *player, SfdMpv *mpv, int *ok);
SfdPicture *sfmpv_GetHd(SfdPlayer *player);
SfdSlot *SFMPVF_SearchFrmObj(SfdPlayer *player, char *body);
int SFMPVF_IsTermDec(SfdPlayer *player);
int SFMPVF_GetNumFrm(SfdPlayer *player);
void SFMPVF_EndDrawFrm(SfdSlot *slot);
SfdSlot *SFMPVF_HoldFrm(SfdPlayer *player, int *out);
SfdSlot *SFMPVF_AllocFrm(SfdPlayer *player);
void SFMPVF_EndRefFrm(SfdSlot *slot);
int FUN_002a8878(SfdPlayer *player);
SfdSlot *sfmpvf_ReferNextFrmReady(SfdPlayer *player);
void sfmpvf_SearchStbyFrm(SfdPlayer *player, SfdSlot **best, SfdSlot **second);
int sfmpvf_IsChkFirst(SfdSlot *a, SfdSlot *b);
void sfmpv_UpdateFlowCnt(SfdPlayer *player);
int sfmpv_NeedSafeDlmRefresh(SfdRingInfo *ring, SfdDelim code, char *dlm);
int sfmpv_CalcDistance(SfdRingInfo *ring, char *addr);
int sfmpv_CheckViBufSiz(SfdPlayer *player);
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
    sfmpv_para = *cond;
    sfmpv_para.f16 = (sfmpv_para.f16 + 0x3F) & ~0x3F;
    sfmpv_para.f32 = (sfmpv_para.f32 + 0x3F) & ~0x3F;
    memset(&sfmpv_rfb_adr_tbl, 0, 8);
    memset(&sfmpv_ta_adr_tbl, 0, 0x40);
}

void SFD_SetMpvParaTbl(SfdMpvCond *cond, int *work, int *bufs)
{
    int i;
    int count;
    sfmpv_para = *cond;
    sfmpv_para.f16 = 0;
    sfmpv_para.f32 = 0;
    for (i = 0; i < 2; i++)
        sfmpv_rfb_adr_tbl.w[i] = (work[i] + 63) & ~63;
    count = cond->count;
    for (i = 0; i < 16; i++) {
        if (i < count)
            sfmpv_ta_adr_tbl.w[i] = (bufs[i] + 63) & ~63;
        else
            sfmpv_ta_adr_tbl.w[i] = 0;
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

void SFD_SetMpvCond(void *sfd, int mode, int value) {
    SfdPlayer *player = sfd;
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

int SFMPV_SaveCond(void *sfd, int *values, unsigned int size) {
    SfdPlayer *player = sfd;
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

void SFMPV_RestoreCond(void *sfd, int *values, int count) {
    SfdPlayer *player = sfd;
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

int SFD_GetNumFrm(void *sfd, int *out) {
    SfdPlayer *player = sfd;
    *out = 0;
    if (SFLIB_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000182);
    }
    *out = SFMPVF_GetNumFrm(player);
    return 0;
}

int SFD_SetVideoUsrSj(SfdPlayer *player, int index, SfdSj *sj, M2vUsrDatFn fn, void *obj) {
    SfdMpv *mpv;
    if (SFLIB_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000184);
    }
    mpv = player->streams.hn.mpv;
    MPV_SetUsrSj(mpv->handle, index, sj, fn, obj);
    return 0;
}

void SFD_SetPicUsrBuf(void *sfd, char *base, int count, int size) {
    SfdPlayer *player = sfd;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000185);
        return;
    }
    sfmpv_SetPicUsrBuf(player, base, count, size);
}

int sfmpv_SetPicUsrBuf(SfdPlayer *player, char *base, int count, int size)
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
    result = MPV_Init(8, sfmpv_work);
    if (result != 0) {
        return sfd_ReportError(0, (result == (int)0xFF03FF05) ? 0xFF000F13 : 0xFF000F01);
    }
    memset(&sfmpv_para, 0, 36);
    memset(&sfmpv_rfb_adr_tbl, 0, 8);
    memset(&sfmpv_ta_adr_tbl, 0, 64);
    sfmpv_discard_wsiz = 0;
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
        status = sfmpv_DecodeSomePic(player);
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
    idx = SFTRN_IsSetup(player, 1) == 0;
    if (SFBUF_GetWTot(player, idx) < SFBUF_GetRingBufSiz(player, idx))
        return 0;
    return 1;
}

void sfmpv_FixedStartTtu(SfdPlayer *player) {
    SfdTimeRec *stamp = &player->tim.vofst;
    if (stamp->time != 0x7FFFFFFF) {
        stamp->valid = 1;
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

int sfmpv_DecodeSomePic(SfdPlayer *player) {
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
    sfmpv_UpdateFlowCnt(player);
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
    SfdTimeRec *stamp = &player->tim.tot;
    SfdStreams *streams = &player->streams;
    int index = streams->f16;
    if (streams->f32 < 0) streams->f32 = SFBUF_GetRTot(player, index) + 4;
    if (stamp->time < 0) *stamp = player->tim.best;
}

int sfmpv_Concat(SfdPlayer *player, SfdStream *stream) {
    if (sfmpv_ConcatSub(player) == -1) {
        return -1;
    }
    sfmpv_DiscardSec(player, stream);
    return 0;
}

int sfmpv_ConcatSub(SfdPlayer *player) {
    SfdTim *timer = &player->tim;
    SfdMpv *mpv = player->streams.hn.mpv;
    int count;
    if (SFSET_GetCond(player, 6) == 0) {
        count = sfmpv_CalcVideoTotTime(player);
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

int sfmpv_CalcVideoTotTime(SfdPlayer *player) {
    SfdTimeRec *state = &player->tim.state;
    SfdTimeCode tc;
    int position;
    int size;
    /* matching construct: manual — best.done/best.tc read through the player, state.a through the state pointer */
    if (player->tim.best.valid == 0) {
        return 0;
    }
    sfmpv_NextTc(&player->tim.best.tc, &tc);
    tc.add = 0;
    SFTIM_Tc2Time(&tc, &position, &size);
    return position - state->time;
}

void sfmpv_DiscardSec(SfdPlayer *player, SfdStream *stream) {
    int buf[4];
    for (;;) {
        stream->ops->read(stream, 1, 4, buf);
        if (buf[1] != 4 || MPV_CheckDelim((const unsigned char *)buf[0]) != 128) {
            break;
        }
        stream->ops->skip(stream, 0, buf);
        sfmpv_AddRtotSj(player, 4);
    }
    stream->ops->end(stream, 1, buf);
}

void sfmpv_AddRtotSj(SfdPlayer *player, int amount) {
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
    long long time;
    long long pts;
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
    sfmpv_AddRtotSj(player, moved);
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
    sfmpv_SetHeadTtu(player, pic);
    sfmpv_SetDecTtu(player, pic);
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

long long sfmpv_ComplementPts(SfdTim *timer, SfdRecord *record, M2vPicAtr *pic, SfdRecordTail *entry, int newGop, long long *pts) {
    int rate = SFTIM_prate[pic->frame_rate_code];
    int number = pic->temporal_reference;
    long long origin;
    long long time;
    int distance;

    if (timer->baseTime < 0) {
        origin = entry->f0 - sfmpv_Nfrm2Pts(number, rate);
        if (origin < 0) {
            origin = 0;
        }
        timer->baseTime = origin;
    }
    time = entry->f0 - timer->baseTime;
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
        time += sfmpv_Nfrm2Pts(record->f4 + distance, rate);
        if (time < 0) {
            time = 0;
        }
    }
    return time;
}

long long sfmpv_Nfrm2Pts(int count, int rate) {
    return (long long)count * 90000000 / rate;
}

/* repeat_first_field accounting: the field offset of each picture of the group, kept by temporal reference */
void sfmpv_CalcRepeatField(SfdPlayer *player, M2vPicAtr *pic, int newGop) {
    SfdTim *timer = &player->tim;
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
            fields[i].repeat = -1;
        }
        fields[0].total = -1;
    } else if (pic->picture_coding_type == 1 || pic->picture_coding_type == 2) {
        ref = mpv->second;
        cur = pic->temporal_reference;
        last = ref->info.temporal_reference;
        if (cur < last) {
            cur += 1024;
        }
        for (t = last + 1; t < cur; t++) {
            fields[t % 64].repeat = -1;
        }
    }
    idx = pic->temporal_reference % 64;
    fields[idx].repeat = timer->tc.repeat;
    if (newGop != 0) {
        fields[idx].total = 0;
    } else if (pic->temporal_reference == 0 && (short)fields[0].total == -1) {
        fields[0].total = 0;
    } else {
        for (i = 0; i < 64; i++) {
            j = (idx - i + 63) % 64;
            if (fields[j].repeat != -1) {
                fields[idx].total = fields[j].repeat + fields[j].total;
                break;
            }
        }
    }
    timer->tc.field = fields[idx].total;
    if (pic->picture_coding_type == 3 && fields[idx].repeat != 0) {
        j = mpv->second->info.temporal_reference % 64;
        fields[j].total = fields[idx].repeat + fields[idx].total;
        mpv->second->stamp.tc.field = fields[j].total;
        FUN_002a54d0(player, mpv->second);
        sfmpv_SetFrmTime(player, mpv->second);
    }
}

void FUN_002a54d0(SfdPlayer *player, SfdSlot *slot) {
    int t[2];
    SfdTim *timer;
    int d;
    timer = &player->tim;
    SFTIM_Tc2Time(&slot->stamp.tc, &t[0], &t[1]);
    d = t[0] - timer->state.time;
    slot->stamp.valid = 1;
    slot->stamp.time = d;
    slot->stamp.unit = t[1];
    if (d >= timer->best.time) {
        timer->best = slot->stamp;
    }
}

void sfmpv_ReformTc(SfdPlayer *player, M2vPicAtr *pic, long long a, int b) {
    int enabled = SFSET_GetCond(player, 52);
    if (enabled == 0) {
        if (a >= 0 || pic->gsc_count == 0 || pic->repeat_first_field != 0
            || (b != 0 && sfmpv_DetectTcErr(player, pic) != 0)) {
            enabled = 1;
            SFSET_SetCond(player, 52, 1);
        }
    }
    if (enabled == 1) {
        sfmpv_DoReformTc(player, pic, a, b);
    }
}

int sfmpv_DetectTcErr(SfdPlayer *player, M2vPicAtr *pic) {
    SfdTimeCode tc;
    int now;
    int rate;
    int start;
    int span;
    if (player->tim.best.valid == 0) {
        return 0;
    }
    tc = player->tim.tc;
    SFTIM_Tc2Time(&tc, &now, &rate);
    SFTIM_Tc2Time(&player->tim.best.tc, &start, &rate);
    span = SFSET_GetCond(player, 53) * rate;
    if (now <= start) {
        return 1;
    }
    if (now < start + span) {
        return 0;
    }
    return 1;
}

void sfmpv_DoReformTc(SfdPlayer *player, M2vPicAtr *pic, long long id, int flag)
{
    SfdTim *timer = &player->tim;
    int b = pic->drop_frame_flag;
    int a = pic->frame_rate_code;
    int idx = pic->temporal_reference;
    if (flag != 0 && id >= 0) {
        sfmpv_Pts2Tc(id, a, b, idx, &player->tim.tc);
        return;
    }
    if (timer->best.valid == 0) {
        if (player->userWork == 0) {
            timer->tc.rate = a;
            timer->tc.drop = 0;
            timer->tc.hour = 0;
            timer->tc.minute = 0;
            timer->tc.second = 0;
            timer->tc.frame = 0;
        }
    } else if (flag != 0) {
        sfmpv_NextTc(&timer->best.tc, &timer->tc);
        timer->fields[0].total = timer->tc.field;
        timer->fields[idx].total = timer->tc.field;
    } else {
        timer->tc.rate = timer->best.tc.rate;
        timer->tc.drop = timer->best.tc.drop;
        timer->tc.hour = timer->best.tc.hour;
        timer->tc.minute = timer->best.tc.minute;
        timer->tc.second = timer->best.tc.second;
        timer->tc.frame = timer->best.tc.frame;
    }
}

void sfmpv_Pts2Tc(long long pts, int prate, int drop, int tmpref, SfdTimeCode *tc)
{
    int rnd = sfmpv_fps_round[prate];
    int rate = SFTIM_prate[prate];
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
        tbl = (rate == 29970) ? sfmpv_conv_29_97 : sfmpv_conv_59_94;
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

void sfmpv_SetHeadTtu(SfdPlayer *player, M2vPicAtr *pic)
{
    SfdTimeRec *state = &player->tim.state;
    SfdTimeCode tc;
    int a, b;
    if (state->valid != 0)
        return;
    tc = player->tim.tc;
    tc.add = 0;
    SFTIM_Tc2Time(&tc, &a, &b);
    state->tc = tc;
    state->time = a;
    state->unit = b;
    state->valid = 1;
}

void sfmpv_SetDecTtu(SfdPlayer *player, M2vPicAtr *pic)
{
    SfdTimeRec *state = &player->tim.state;
    SfdTimeCode tc;
    int a, b;
    SfdTimeRec *cur;
    SfdTimeRec *best;
    int d;
    tc = player->tim.tc;
    SFTIM_Tc2Time(&tc, &a, &b);
    player->tim.cur.tc = tc;
    cur = &player->tim.cur;
    best = &player->tim.best;
    d = a - state->time;
    cur->valid = 1;
    cur->time = d;
    cur->unit = b;
    if (d >= best->time)
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
    out->repeat = (signed char)pic->field_count;
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
    SfdTim *timer;
    picture = sfmpv_GetHd(player);
    if (picture == 0 || picture->valid != 0)
        return;
    len = chunk->size;
    user = &picture->user;
    if (len > 512)
        len = 512;
    timer = &player->tim;
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
    return player->tim.tally.total >= 0;
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
    sfmpv_UpdateDefect(player, pic, skip);
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

void sfmpv_UpdateDefect(SfdPlayer *player, M2vPicAtr *pic, int kind)
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
            if (player->tim.vofst.valid == 0 && SFSET_GetCond(player, 73) == 1)
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
    SfdTimeRec *cur = &player->tim.cur;
    SfdTimeRec *f280 = &player->tim.vofst;
    if (link->id < 0) {
        return 0;
    }
    if (f280->valid != 0) {
        return 0;
    }
    return UTY_CmpTime(link->id, link->arg, cur->time, cur->unit) == 0;
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
    SfdTim *timer = &player->tim;
    SfdTimeRec *cur = &timer->cur;
    SfdTimeRec *ofs = &timer->vofst;
    int time;
    int unit;
    int now;
    int nowUnit;
    int dnum;
    int dden;

    if (ofs->valid == 0) {
        time = 0;
    } else {
        time = cur->time - ofs->time + timer->tally.total;
    }
    unit = cur->unit;
    if (timer->isSkipFn != 0) {
        return timer->isSkipFn(player, type, time, unit);
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
    sfmpv_AddRtotSj(player, used);
    if (ret != 0)
        return ret;
    if (pic->field_964 == 0)
        mpv->f364 = 1;
    SFPLY_AddSkipPic(player, 1, pic->picture_coding_type);
    return 0;
}

void sfmpv_SetSkipTtu(SfdPlayer *player) {
    SfdTimeRec *current = &player->tim.cur;
    SfdTimeRec *latest = &player->tim.latest;
    if (current->time < player->tim.vofst.time) {
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
    SfdTimeRec *state2 = &player->tim.vofst;
    SfdTimeRec *state = &player->tim.state;
    SfdTimeCode tc;
    int a, b;
    if (state2->valid != 0)
        return;
    tc = player->tim.cur.tc;
    if (sfmpv_IsDefect(player, 3) == 0 && sfmpv_IsPtypeSkip(player, 3) == 0)
        tc.add = 0;
    SFTIM_Tc2Time(&tc, &a, &b);
    state2->tc = tc;
    state2->time = a - state->time;
    state2->unit = b;
    state2->valid = 1;
}

void FUN_002a7040(SfdPlayer *player, SfdSlot *slot) {
    slot->stamp = player->tim.cur;
    if (SFMPVP_IsSceMpegUsed(player) != 0) {
        slot->f224 = SFMPVP_GetFrameCount(player);
    }
    sfmpv_SetFrmTime(player, slot);
}

void sfmpv_SetFrmTime(SfdPlayer *player, SfdSlot *slot) {
    SfdTim *timer = &player->tim;
    SfdTimeRec *in = &slot->stamp;
    int t;
    slot->f60 = in->unit;
    slot->f56 = in->time - player->tim.vofst.time + timer->tally.total;
    slot->f76 = in->time;
    slot->f80 = in->time + timer->tally.total;
    if (SFMPVP_IsSceMpegUsed(player) != 0) {
        t = UTY_MulDiv(slot->f60, (slot->f224 - timer->f352) * 1000, SFTIM_prate[slot->info.frame_rate_code]);
        slot->f76 = t;
        slot->f56 = slot->f80 = t + timer->tally.total;
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

void sfmpv_UpdateFlowCnt(SfdPlayer *player) {
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
    if (MPV_EntryErrFunc(dec, sfmpv_ErrFn, player) != 0) {
        sfmpv_DestroySub(dec);
        return sfd_ReportError(0, 0xFF000F0B);
    }
    MPV_SetCond(dec, 1, SFSET_GetCond(player, 0));
    MPV_SetCond(dec, 2, SFSET_GetCond(player, 1));
    MPV_SetCond(dec, 6, player->bufFmt);
    mpv->handle = dec;
    if (SFPLY_GetResetFlg() != 0)
        sfmpv_SetPicUsrBuf(player, sfmpv_picusr_pbuf, sfmpv_picusr_bufnum, sfmpv_picusr_buf1siz);
    return 0;
}

int sfmpv_InitInf(SfdPlayer *player, SfdMpv *mpv) {
    int i;

    if (sfmpv_CheckMpvPara() != 0) {
        return sfd_ReportError(0, 0xFF000F15);
    }
    mpv->cond = sfmpv_para;
    mpv->work = sfmpv_rfb_adr_tbl;
    mpv->bufs = sfmpv_ta_adr_tbl;
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
    if ((unsigned)(sfmpv_para.count - 1) >= 16) {
fail:
        return -1;
    }
    if (sfmpv_para.f16 == 0 || sfmpv_para.f32 == 0) {
        for (i = 0; i < 2; i++) {
            if (sfmpv_rfb_adr_tbl.w[i] == 0) goto fail;
        }
        for (i = 0; i < sfmpv_para.count; i++) {
            if (sfmpv_ta_adr_tbl.w[i] == 0) goto fail;
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

void sfmpv_ErrFn(SfdPlayer *player, int code) {
    if (code < -3 || (code >= -1 && code != 0)) {
        sfd_ReportError(player, code);
    }
}

int SFMPV_Destroy(SfdPlayer *player)
{
    SfdMpv *mpv = player->streams.hn.mpv;
    void *dec = mpv->handle;
    if (dec == 0)
        return 0;
    sfmpv_para = mpv->cond;
    sfmpv_rfb_adr_tbl = mpv->work;
    sfmpv_ta_adr_tbl = mpv->bufs;
    sfmpv_picusr_pbuf = mpv->pool.base;
    sfmpv_picusr_bufnum = mpv->pool.count;
    sfmpv_picusr_buf1siz = mpv->pool.size;
    SFMPVP_Destroy(player);
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
    SfdTim *timer = &player->tim;
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
    timer->base = (*out)->f20;
    timer->base_frames = (*out)->f24;
    return 0;
}

/* matching construct: placement — declared here; with the other declarations it changes the
 * address-taken local loads of sfmpv_SetDecTtu */
SfdPicRecord *SFMPVF_SearchVfrmData(SfdPlayer *player, SfdSlot *target);

/* fills the frame information handed to the application from the frame's slot and marks its record
 * in use */
void sfmpv_SetFrmInf(SfdPlayer *player, SfdSlot *slot, SfdFrameInfo **out) {
    SfdMpv *mpv = player->streams.hn.mpv;
    M2vPicAtr *pic = &slot->info;
    SfdPicRecord *record;

    record = SFMPVF_SearchVfrmData(player, slot);
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
    result = sfmpv_AddReadSub(player, body);
    sfd_Unlock(guard);
    return result;
}

int sfmpv_AddReadSub(SfdPlayer *player, char *body) {
    SfdMpv *mpv = player->streams.hn.mpv;
    SfdPicRecord *record = FUN_002a8158(player, body);
    SfdSlot *found;
    SfdSlot *current;
    if (record->f0 != 1) {
        return sfd_ReportError(player, 0xFF000F0E);
    }
    found = SFMPVF_SearchFrmObj(player, body);
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
    player->tim.state = picture->stamp;
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

void SFD_LockFrm(SfdPlayer *player, char *body) {
    SfdSlot *slot;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000188);
        return;
    }
    slot = SFMPVF_SearchFrmObj(player, body);
    if (slot == 0) {
        sfd_ReportError(player, 0xFF000F30);
    } else {
        slot->refs++;
    }
    player->decode.f44++;
}

void SFD_UnlockFrm(SfdPlayer *player, char *body) {
    SfdSlot *slot;
    int count;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000189);
    } else {
        slot = SFMPVF_SearchFrmObj(player, body);
        if (slot == 0) {
            sfd_ReportError(player, 0xFF000F31);
        } else {
            count = slot->refs - 1;
            slot->refs = count < 0 ? 0 : count;
        }
        player->decode.f44--;
    }
}

SfdSlot *SFMPVF_SearchFrmObj(SfdPlayer *player, char *body) {
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

SfdPicRecord *SFMPVF_SearchVfrmData(SfdPlayer *player, SfdSlot *target) {
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
        if (*(long long *)slot == 0) {
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

void SFD_GetNextPicUsr(void *sfd, char **data, int *size) {
    SfdPlayer *player = sfd;
    SfdSlot *slot = sfmpvf_ReferNextFrmReady(player);
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

int SFD_GetNumRemainFrm(void *sfd) {
    SfdPlayer *player = sfd;
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
    sfmpvf_SearchStbyFrm(player, &p, &q);
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

int SFD_IsNextFrmReady(void *sfd) {
    SfdPlayer *player = sfd;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000183);
        return 0;
    }
    return sfmpvf_ReferNextFrmReady(player) != 0;
}

SfdSlot *sfmpvf_ReferNextFrmReady(SfdPlayer *player) {
    int guard;
    SfdSlot *best;
    SfdSlot *second;
    sfd_Lock(&guard);
    if (player->f72 != 4) {
        second = 0;
    } else {
        sfmpvf_SearchStbyFrm(player, &best, &second);
        if (second != 0 && SFSET_GetCond(player, 15) != 0) {
            if (SFTIM_IsGetFrmTimeTunit(player, second->f56, second->f60) == 0) {
                second = 0;
            }
        }
    }
    sfd_Unlock(&guard);
    return second;
}

void sfmpvf_SearchStbyFrm(SfdPlayer *player, SfdSlot **best, SfdSlot **second) {
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
