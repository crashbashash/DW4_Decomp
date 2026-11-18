#include "dw4/cri/sfdply.h"
#include "dw4/cri/mpv.h"
#include <string.h>
#include "dw4/cri/mps.h"
#include "dw4/cri/uty.h"
#include <stddef.h>
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
int MPV_EntryErrFunc(void *handle, void (*callback)(SfdPly *, int), SfdPly *player);
char *sfmpv_SearchDelim(SfdBufStat *ring, int mask, SfdDelim *code);
char *sfmpv_BsearchDelim(SfdBufStat *ring, int mask, SfdDelim *code);
void FUN_002a7278(SfdSj *source, int *kind, char **data, int *size);
void sfmpv_InitPicUsr(SfdBufPool *pool);
void sfmpv_SetFrmInf(SfdPly *player, SfdSlot *slot, SfdFrameInfo **out);

int sfmpv_SetPicUsrBuf(SfdPly *player, char *base, int count, int size);
int sfmpv_ChkFatal(void);
int sfmpv_ExecServerSub(SfdPly *player);
void sfmpv_SetCondY16(SfdPly *player);
void FUN_002a3850(SfdPly *player);
int sfmpv_GetTermDst(SfdPly *player);
void sfmpv_ChkPrepFlg(SfdPly *player);
int sfmpv_IsPrepEnd(SfdPly *player);
int sfmpv_IsPrepFrmEnough(SfdPly *player);
int sfmpv_IsVbvEnough(SfdPly *player);
void sfmpv_FixedStartTtu(SfdPly *player);
void sfmpv_ChkTermFlg(SfdPly *player);
void sfmpv_SetTermDst(SfdPly *player, int value);
int sfmpv_DecodeSomePic(SfdPly *player);
int sfmpv_GetActiveSize(SfdPly *player, int *size, int *code, int *flag);
int sfmpv_DecodeOneUnit(SfdPly *player, int size, int code, int flag, int *done);
int sfmpv_ConcatSub(SfdPly *player);
int sfmpv_CalcVideoTotTime(SfdPly *player);
int sfmpv_CalcAudioTotTime(SfdPly *player);
void sfmpv_DiscardSec(SfdPly *player, SfdSj *stream);
void sfmpv_AddRtotSj(SfdPly *player, int amount);
int sfmpv_GetTermSrc(SfdPly *player);
int sfmpv_ChkMpvErr(SfdPly *player, int status, int n, int code);
void sfmpv_ReadPtsQue(SfdPly *player, M2vPicAtr *pic, char *pos, long long *time, long long *pts, int newGop);
long long sfmpv_ComplementPts(SfdTim *timer, SfdPtsComp *comp, M2vPicAtr *pic, SfdItem *entry, int newGop, long long *pts);
long long sfmpv_Nfrm2Pts(int count, int rate);
void FUN_002a54d0(SfdPly *player, SfdSlot *slot);
void sfmpv_ReadTcode(M2vPicAtr *pic, SfdTimeCode *out);
int sfmpv_DetectTcErr(SfdPly *player, M2vPicAtr *pic);
void sfmpv_DoReformTc(SfdPly *player, M2vPicAtr *pic, long long id, int flag);
void sfmpv_Pts2Tc(long long pts, int prate, int drop, int tmpref, SfdTimeCode *tc);
void sfmpv_NextTc(SfdTimeCode *src, SfdTimeCode *dst);
void sfmpv_SetMpvHd(SfdPly *player, int pts, SfdSjChunk *chunk);
void sfmpv_SetMvInf(SfdMvInf *geom, int pts, M2vPicAtr *pic, int x);
int sfmpv_ChkBufSiz(SfdPly *player, SfdMvInf *geom);
int sfmpv_IsDefect(SfdPly *player, int kind);
int sfmpv_IsPtypeSkip(SfdPly *player, unsigned int kind);
void sfmpv_SetSkipTtu(SfdPly *player);
int sfmpv_IsSeekSkip(SfdPly *player);
int sfmpv_IsEmptySkip(SfdPly *player, unsigned int type, SfdSjChunk *chunk);
int sfmpv_IsLate(SfdPly *player, unsigned int type);
void sfmpv_GetDtime(SfdPly *player, int unused, int *first, int *second);
void sfmpv_UpdateDefect(SfdPly *player, M2vPicAtr *pic, int kind);
void sfmpv_SetFrmTime(SfdPly *player, SfdSlot *slot);
void FUN_002a73f0(SfdSjChunk *dst, SfdSjChunk *src);
void sfmpv_RingAddRead(SfdPly *player, int n);
int sfmpv_InitInf(SfdPly *player, SfdMpv *mpv);
int sfmpv_CheckMpvPara(void);
void sfmpv_InitFrmObj(SfdSlot *slot, int *ids, int count);
void sfmpv_InitPicAtr(M2vPicAtr *info);
void sfmpv_ErrFn(SfdPly *player, int code);
int sfmpv_DestroySub(void *handle);
int sfmpv_AddReadSub(SfdPly *player, char *body);
SfdVfrm *FUN_002a8158(SfdPly *player, char *body);
int sfmpv_ReprocessShc(SfdPly *player, SfdMpv *mpv, int *ok);
SfdRecVideo *sfmpv_GetHd(SfdPly *player);
SfdSlot *SFMPVF_SearchFrmObj(SfdPly *player, char *body);
int SFMPVF_IsTermDec(SfdPly *player);
int SFMPVF_GetNumFrm(SfdPly *player);
void SFMPVF_EndDrawFrm(SfdSlot *slot);
SfdSlot *SFMPVF_HoldFrm(SfdPly *player, int *out);
SfdSlot *SFMPVF_AllocFrm(SfdPly *player);
void SFMPVF_EndRefFrm(SfdSlot *slot);
int FUN_002a8878(SfdPly *player);
SfdSlot *sfmpvf_ReferNextFrmReady(SfdPly *player);
void sfmpvf_SearchStbyFrm(SfdPly *player, SfdSlot **best, SfdSlot **second);
int sfmpvf_IsChkFirst(SfdSlot *a, SfdSlot *b);
void sfmpv_UpdateFlowCnt(SfdPly *player);
int sfmpv_NeedSafeDlmRefresh(SfdBufStat *ring, SfdDelim code, char *dlm);
int sfmpv_CalcDistance(SfdBufStat *ring, char *addr);
int sfmpv_CheckViBufSiz(SfdPly *player);
void SFMPVF_TermDec(SfdPly *player);
SfdMpv *SFMPVF_SetGopStat(SfdPly *player, int value);
void sfmpv_PeekChnk(SfdPly *player, SfdSjChunk *out);
void sfmpv_FixedForSeek(SfdPly *player);
int sfmpv_Concat(SfdPly *player, SfdSj *stream);
int sfmpv_IsTerm(SfdPly *player, int level, int kind);
int sfmpv_IsSkip(SfdPly *player, SfdSjChunk *chunk);
int sfmpv_SkipFrm(SfdPly *player, SfdSj *sj);
int sfmpv_DecodePicAtr(SfdPly *player, SfdSjChunk *chunk, SfdSj *sj, int code, int *result);
int sfmpv_DecodeFrm(SfdPly *player, SfdSj *sj);
int sfmpv_GoDdelim(SfdPly *player, SfdSj *sj, int mask);
void sfmpv_CalcRepeatField(SfdPly *player, M2vPicAtr *pic, int newGop);
void sfmpv_ReformTc(SfdPly *player, M2vPicAtr *pic, long long a, int b);
void sfmpv_SetHeadTtu(SfdPly *player, M2vPicAtr *pic);
void sfmpv_SetDecTtu(SfdPly *player, M2vPicAtr *pic);

void SFD_SetMpvPara(SfdMpvCond *cond) {
    sfmpv_para = *cond;
    sfmpv_para.rfb_adr = (sfmpv_para.rfb_adr + 0x3F) & ~0x3F;
    sfmpv_para.ta_adr = (sfmpv_para.ta_adr + 0x3F) & ~0x3F;
    memset(&sfmpv_rfb_adr_tbl, 0, 8);
    memset(&sfmpv_ta_adr_tbl, 0, 0x40);
}

void SFD_SetMpvParaTbl(SfdMpvCond *cond, int *work, int *bufs)
{
    int i;
    int count;
    sfmpv_para = *cond;
    sfmpv_para.rfb_adr = 0;
    sfmpv_para.ta_adr = 0;
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
    int columns = (cond->rfb_width + 15) / 16;
    int rows;
    int lumaBlocks = (columns * 16 + 63) / 64;
    int chromaBlocks;
    char *base;
    rows = (cond->rfb_height + 15) / 16;
    chromaBlocks = (columns * 8 + 63) / 64;
    base = (char *)cond->ta_adr;
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
    SfdPly *player = sfd;
    void *h = 0;
    if (player != 0) {
        SfdMpv *mpv;
        if (SFLIB_CheckHn(player) != 0) {
            sfd_ReportError(0, 0xff000181);
            return;
        }
        mpv = player->trn[2].hn.mpv;
        h = mpv->handle;
    }
    if (MPV_SetCond(h, mode, mode != 5 ? value : 0) != 0) {
        sfd_ReportError(player, 0xff000f12);
        return;
    }
}

int SFMPV_SaveCond(void *sfd, int *values, unsigned int size) {
    SfdPly *player = sfd;
    SfdMpv *mpv = player->trn[2].hn.mpv;
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
    SfdPly *player = sfd;
    SfdMpv *mpv;
    int *value;
    int index;
    void *handle;
    mpv = player->trn[2].hn.mpv;
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
    SfdPly *player = sfd;
    *out = 0;
    if (SFLIB_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000182);
    }
    *out = SFMPVF_GetNumFrm(player);
    return 0;
}

int SFD_SetVideoUsrSj(SfdPly *player, int index, SfdSj *sj, M2vUsrDatFn fn, void *obj) {
    SfdMpv *mpv;
    if (SFLIB_CheckHn(player) != 0) {
        return sfd_ReportError(0, 0xFF000184);
    }
    mpv = player->trn[2].hn.mpv;
    MPV_SetUsrSj(mpv->handle, index, sj, fn, obj);
    return 0;
}

void SFD_SetPicUsrBuf(void *sfd, char *base, int count, int size) {
    SfdPly *player = sfd;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000185);
        return;
    }
    sfmpv_SetPicUsrBuf(player, base, count, size);
}

int sfmpv_SetPicUsrBuf(SfdPly *player, char *base, int count, int size)
{
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdBufPool *pool = &mpv->pool;
    int i;
    if (base == 0 || count == 0 || size == 0) {
        sfmpv_InitPicUsr(pool);
        return 0;
    }
    if (count < player->cre.f44 + 4)
        return sfd_ReportError(player, 0xFF000F1D);
    pool->base = base;
    i = 0;
    pool->slot[0].data = base;
    base += size;
    pool->count = count;
    count -= 2;
    pool->slot[1].data = base;
    base += size;
    pool->size = size;
    pool->slot[0].len = 0;
    pool->slot[1].len = 0;
    for (; i < (count < 17 ? count : 16); i++) {
        pool->slot[i + 2].len = 0;
        pool->slot[i + 2].data = base;
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

void SFMPV_ExecServer(SfdPly *player) {
    sfmpv_ExecServerSub(player);
}

int sfmpv_ExecServerSub(SfdPly *player) {
    int status;
    int result;
    result = SFSET_GetCond(player, 5);
    if (result != 0) {
        if (sfmpv_GetTermDst(player) == 1) {
            return 0;
        }
        sfmpv_SetCondY16(player);
        if (player->stat == 2) {
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

void sfmpv_SetCondY16(SfdPly *player) {
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

void FUN_002a3850(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    void *handle = mpv->handle;
    SfdSjChunk seqhd;
    int result[4];
    seqhd.data = (char *)SFSET_GetCond(player, 93);
    seqhd.len = SFSET_GetCond(player, 94);
    if (seqhd.data != 0 && seqhd.len != 0 && mpv->dlmmask == 192) {
        if (MPV_DecodePicAtr(handle, &seqhd, result) == 0) {
            mpv->picstat = 2;
            mpv->dlmmask = 200;
        }
    }
}

int sfmpv_GetTermDst(SfdPly *player) {
    return SFBUF_GetTermFlg(player, player->trn[2].bufOut[0]);
}

void sfmpv_ChkPrepFlg(SfdPly *player) {
    SfdTrnSlot *streams = &player->trn[2];
    int target = streams->bufOut[0];
    int source = streams->bufIn;
    if (SFBUF_GetPrepFlg(player, target) != 1 && SFBUF_GetPrepFlg(player, source) == 1 && sfmpv_IsPrepEnd(player) != 0) {
        SFBUF_SetPrepFlg(player, target, 1);
        sfmpv_FixedStartTtu(player);
    }
}

int sfmpv_IsPrepEnd(SfdPly *player) {
    if ((SFMPVF_IsTermDec(player) != 0) || ((sfmpv_IsPrepFrmEnough(player) != 0) && (sfmpv_IsVbvEnough(player) != 0))) {
        return 1;
    }
    return 0;
}

int sfmpv_IsPrepFrmEnough(SfdPly *player) {
    int limit = player->cond[23];
    int size = player->cre.f44;
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

int sfmpv_IsVbvEnough(SfdPly *player)
{
    SfdMpv *mpv = player->trn[2].hn.mpv;
    void *handle = mpv->handle;
    SfdHdrInf *hdr = &player->hdr;
    int value;
    int idx;
    if (sfmpv_GetTermSrc(player) == 1)
        return 1;
    if (hdr->valid != 0 && hdr->video.flag0 == 0)
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

void sfmpv_FixedStartTtu(SfdPly *player) {
    SfdTimeRec *stamp = &player->tim.vofst;
    if (stamp->time != 0x7FFFFFFF) {
        stamp->valid = 1;
    }
}

void sfmpv_ChkTermFlg(SfdPly *player) {
    SfdPlyInf *decode = &player->plyInf;
    int status = SFMPVF_GetNumFrm(player);
    if (status == -1 || (SFMPVF_IsTermDec(player) != 0 && status == 1 && decode->frmOut != 0)) {
        sfmpv_SetTermDst(player, 1);
        if (decode->numTotalDec == 0) {
            SFSET_SetCond(player, 5, 0);
        }
    }
}

void sfmpv_SetTermDst(SfdPly *player, int value) {
    SFBUF_SetTermFlg(player, player->trn[2].bufOut[0], value);
}

int sfmpv_DecodeSomePic(SfdPly *player) {
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
int sfmpv_GetActiveSize(SfdPly *player, int *size, int *code, int *flag) {
    SfdBufStat inf;
    int bufin = player->trn[2].bufIn;
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
    if (inf.ck0.len == 0)
        return 0;
    p = sfmpv_SearchDelim(&inf, SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC | SFD_DLM_SLICE, &dcode);
    if (p != inf.ck0.data) {
        if (p != 0) {
            *size = sfmpv_CalcDistance(&inf, p);
        } else {
            n = inf.ck0.len + inf.ck1.len - 3;
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
        if (inf.ck1.len == 0)
            end = inf.ck0.data + inf.ck0.len;
        else
            end = inf.ck1.data + inf.ck1.len;
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
int sfmpv_NeedSafeDlmRefresh(SfdBufStat *ring, SfdDelim code, char *dlm) {
    char tmp[4];
    int n;
    char *p;

    if (dlm == 0)
        return 1;
    if (dlm == ring->ck0.data)
        return 1;
    if (dlm > ring->ck0.data) {
        if (dlm - ring->ck0.data < 4)
            return 1;
    }
    if (dlm >= ring->ck0.data && dlm < ring->ck0.data + ring->ck0.len) {
        n = dlm + 4 - (ring->ck0.data + ring->ck0.len);
        if (n > 0) {
            if (n > ring->ck1.len)
                return 1;
            memcpy(tmp, dlm, 4 - n);
            memcpy(tmp + 4 - n, ring->ck1.data, n);
        } else {
            memcpy(tmp, dlm, 4);
        }
    } else if (dlm >= ring->ck1.data && dlm < ring->ck1.data + ring->ck1.len) {
        n = dlm + 4 - (ring->ck1.data + ring->ck1.len);
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

int sfmpv_CalcDistance(SfdBufStat *ring, char *addr) {
    int offset;
    if (addr >= ring->ck0.data && addr < ring->ck0.data + ring->ck0.len) {
        offset = addr - ring->ck0.data;
    } else if (addr >= ring->ck1.data && addr < ring->ck1.data + ring->ck1.len) {
        offset = addr - ring->ck1.data + ring->ck0.len;
    } else {
        offset = 0;
    }
    return offset;
}

int sfmpv_CheckViBufSiz(SfdPly *player) {
    int index = player->trn[2].bufIn;
    int total = SFBUF_GetRingBufSiz(player, index);
    if (total - SFBUF_RingGetDataSiz(player, index) < player->cre.unit) {
        return sfd_ReportError(player, 0xFF000F1C);
    }
    return 0;
}

/* Searches the readable data of the ring (two chunks) for a start code in `mask`, including one that
 * straddles the wrap; returns its address and its kind in *code, or 0. */
char *sfmpv_SearchDelim(SfdBufStat *ring, int mask, SfdDelim *code) {
    char tmp[8];
    char *p;
    int n1;
    int n2;
    int i;
    int c;

    *code = 0;
    p = MPV_SearchDelim(ring->ck0.data, ring->ck0.len, mask);
    if (p != 0) {
        *code = MPV_CheckDelim(p);
        return p;
    }
    if (ring->ck1.len == 0) {
        return 0;
    }
    n1 = (ring->ck0.len < 3) ? ring->ck0.len : 3;
    n2 = (ring->ck1.len < 3) ? ring->ck1.len : 3;
    memcpy(tmp, ring->ck0.data + ring->ck0.len - n1, n1);
    memcpy(tmp + n1, ring->ck1.data, n2);
    for (i = 0; i < n1 + n2 - 3; i++) {
        c = MPV_CheckDelim(&tmp[i]);
        if (c & mask) {
            *code = c;
            return ring->ck0.data + ring->ck0.len - n1 + i;
        }
    }
    p = MPV_SearchDelim(ring->ck1.data, ring->ck1.len, mask);
    if (p != 0) {
        *code = MPV_CheckDelim(p);
        return p;
    }
    return 0;
}

/* The same search backwards from the end of the readable data. */
char *sfmpv_BsearchDelim(SfdBufStat *ring, int mask, SfdDelim *code) {
    char tmp[8];
    char *p;
    int n1;
    int n2;
    int i;
    int c;

    *code = 0;
    if (ring->ck1.len != 0) {
        p = MPV_BsearchDelim(ring->ck1.data + ring->ck1.len, ring->ck1.len, mask);
        if (p != 0) {
            *code = MPV_CheckDelim(p);
            return p;
        }
        n1 = (ring->ck0.len < 3) ? ring->ck0.len : 3;
        n2 = (ring->ck1.len < 3) ? ring->ck1.len : 3;
        memcpy(tmp, ring->ck0.data + ring->ck0.len - n1, n1);
        memcpy(tmp + n1, ring->ck1.data, n2);
        for (i = 0; i < n1 + n2 - 3; i++) {
            c = MPV_CheckDelim(&tmp[i]);
            if (c & mask) {
                *code = c;
                return ring->ck0.data + ring->ck0.len - n1 + i;
            }
        }
    }
    p = MPV_BsearchDelim(ring->ck0.data + ring->ck0.len, ring->ck0.len, mask);
    if (p != 0) {
        *code = MPV_CheckDelim(p);
        return p;
    }
    return 0;
}

/* Decodes the start-code-delimited unit at the read position. */
int sfmpv_DecodeOneUnit(SfdPly *player, int size, int code, int flag, int *done) {
    SfdPlyInf *decode = &player->plyInf;
    SfdTrnSlot *streams;
    SfdMpv *mpv;
    int bufin;
    int ret;
    SfdSj *sj;
    int result;
    int picResult;
    SfdSjChunk chunk;

    *done = 0;
    streams = &player->trn[2];
    bufin = streams->bufIn;
    mpv = streams->hn.mpv;
    decode->vidShort = 0;
    if (SFMPVP_IsPscEnough(player) == 0) {
        if (sfmpv_GetTermSrc(player) == 1) {
            SFMPVF_TermDec(player);
            return 0;
        }
        decode->vidShort = 1;
        return sfmpv_CheckViBufSiz(player);
    }
    if (mpv->dlmmask != (SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC) || mpv->dlmwait == 0) {
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
        if (sfmpv_Concat(player, sj) == 0) {
            *done = 1;
        }
    } else if (code == SFD_DLM_END && SFCON_IsVideoEndcodeSkip(player) != 0) {
        sfmpv_DiscardSec(player, sj);
        *done = 1;
    } else if (flag == 0 && sfmpv_IsTerm(player, size, code)) {
        SFMPVF_TermDec(player);
    } else if (flag == 0 && size <= 4) {
        decode->vidShort = 1;
    } else if (code & (SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC)) {
        sfmpv_PeekChnk(player, &chunk);
        ret = sfmpv_DecodePicAtr(player, &chunk, sj, code, &result);
        if (ret != 0) {
            return ret;
        }
        /* held in a local: read from result, it is reloaded after the mpv stores below */
        picResult = result;
        if (picResult == 0) {
            if (code & mpv->dlmmask) {
                mpv->dlmmask = SFD_DLM_END | SFD_DLM_SEQ | SFD_DLM_GOP | SFD_DLM_PIC;
            }
            mpv->dlmwait = 1;
        }
        if (code == SFD_DLM_SEQ && picResult == -2) {
            mpv->dlmmask = SFD_DLM_END | SFD_DLM_SEQ;
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

void sfmpv_PeekChnk(SfdPly *player, SfdSjChunk *out) {
    SfdBufStat info;
    if (SFBUF_RingGetRead(player, player->trn[2].bufIn, &info) != 0) {
        out->data = 0;
        out->len = 0;
    } else {
        out->data = info.ck0.data;
        out->len = info.ck0.len;
    }
}

void sfmpv_FixedForSeek(SfdPly *player) {
    SfdTimeRec *stamp = &player->tim.tot;
    SfdTrnSlot *streams = &player->trn[2];
    int index = streams->bufIn;
    if (streams->readTot < 0) streams->readTot = SFBUF_GetRTot(player, index) + 4;
    if (stamp->time < 0) *stamp = player->tim.best;
}

int sfmpv_Concat(SfdPly *player, SfdSj *stream) {
    if (sfmpv_ConcatSub(player) == -1) {
        return -1;
    }
    sfmpv_DiscardSec(player, stream);
    return 0;
}

int sfmpv_ConcatSub(SfdPly *player) {
    SfdTim *timer = &player->tim;
    SfdMpv *mpv = player->trn[2].hn.mpv;
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
        mpv->nconcat++;
        if (SFMPVP_IsSceMpegUsed(player) != 0) {
            timer->concat_frmcnt = SFMPVP_GetFrameCount(player) + 1;
        }
    }
    SFTIM_InitTtu(&timer->state, 0x7FFFFFFF);
    SFTIM_InitTtu(&timer->best, -1);
    mpv->dlmmask = 192;
    return 0;
}

int sfmpv_CalcVideoTotTime(SfdPly *player) {
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

void sfmpv_DiscardSec(SfdPly *player, SfdSj *stream) {
    SfdSjChunk ck;
    for (;;) {
        stream->vtbl->getChunk(stream, 1, 4, &ck);
        if (ck.len != 4 || MPV_CheckDelim((const unsigned char *)ck.data) != 128) {
            break;
        }
        stream->vtbl->putChunk(stream, 0, &ck);
        sfmpv_AddRtotSj(player, 4);
    }
    stream->vtbl->ungetChunk(stream, 1, &ck);
}

void sfmpv_AddRtotSj(SfdPly *player, int amount) {
    SFBUF_AddRtotSj(player, player->trn[2].bufIn, amount);
    player->plyInf.vidByte += amount;
}

int sfmpv_IsTerm(SfdPly *player, int level, int kind) {
    if (kind == 128) {
        return 1;
    }
    if (level < 5 && sfmpv_GetTermSrc(player) == 1) {
        return 1;
    }
    return 0;
}

int sfmpv_GetTermSrc(SfdPly *player) {
    return SFBUF_GetTermFlg(player, player->trn[2].bufIn);
}

int sfmpv_ChkMpvErr(SfdPly *player, int status, int n, int code)
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
int sfmpv_DecodePicAtr(SfdPly *player, SfdSjChunk *chunk, SfdSj *sj, int code, int *result) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
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

    pool->slot[0].len = 0;
    MPV_SetPicUsrBuf(handle, pool->slot[0].data, pool->size);
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
        if (player->mvInf.width > 0
            && (player->mvInf.width != pic->horizontal_size || player->mvInf.height != pic->vertical_size)) {
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
        mpv->tmpref_adj = 0;
    } else if (player->cre.bufFmt == 3 && mpv->second != 0) {
        last = mpv->second->info.temporal_reference;
        if (pic->picture_coding_type == 2) {
            if (pic->temporal_reference < last && last < 512) {
                mpv->tmpref_adj = 1;
            }
        } else if (pic->picture_coding_type == 3) {
            if (pic->temporal_reference >= last) {
                mpv->tmpref_adj = 1;
            }
        }
    }
    MPV_GetPicUsr(handle, 0, &pool->slot[0].len);
    if (mpv->last_ngop != pic->gsc_count) {
        mpv->last_ngop = pic->gsc_count;
        mpv->newgop = 1;
    } else {
        mpv->newgop = 0;
    }
    if (seq) {
        hdrFn = (void (*)(void *, char *, int))SFSET_GetCond(player, 77);
        hdrObj = (void *)SFSET_GetCond(player, 78);
        if (hdrFn != 0) {
            pos = MPV_SearchDelim(chunk->data, chunk->len, 1);
            if (pos != 0) {
                hdrFn(hdrObj, chunk->data, pos + 4 - chunk->data);
            }
        }
    }
    pos = MPV_SearchDelim(chunk->data, chunk->len, 4);
    sfmpv_ReadPtsQue(player, pic, pos, &time, &pts, mpv->newgop);
    mpv->pts = pts;
    if ((code & mpv->dlmmask) == 0) {
        return 0;
    }
    sfmpv_CalcRepeatField(player, pic, mpv->newgop);
    sfmpv_ReformTc(player, pic, time, mpv->newgop);
    sfmpv_SetHeadTtu(player, pic);
    sfmpv_SetDecTtu(player, pic);
    return sfmpv_FirstPicAtr(player, handle, pic, chunk);
}

void sfmpv_InitComplementPts(SfdPtsComp *comp) {
    SfdItem *ent = &comp->ptsent;
    comp->tmpref = 0;
    comp->ofst = 0;
    comp->max = 0;
    ent->pos = -1;
    ent->size = -1;
    ent->addr = 0;
}

long long sfmpv_ComplementPts(SfdTim *timer, SfdPtsComp *comp, M2vPicAtr *pic, SfdItem *entry, int newGop, long long *pts) {
    int rate = SFTIM_prate[pic->frame_rate_code];
    int number = pic->temporal_reference;
    long long origin;
    long long time;
    int distance;

    if (timer->baseTime < 0) {
        origin = entry->pos - sfmpv_Nfrm2Pts(number, rate);
        if (origin < 0) {
            origin = 0;
        }
        timer->baseTime = origin;
    }
    time = entry->pos - timer->baseTime;
    if (time < 0) {
        time = 0;
    }
    if (memcmp(&comp->ptsent, entry, 4) != 0) {
        int type = pic->picture_coding_type;

        comp->ptsent = *entry;
        comp->tmpref = number;
        comp->ofst = 0;
        if (type == 3) {
            comp->max = 1;
        } else {
            comp->max = 0;
        }
        *pts = entry->pos;
    } else {
        if (newGop) {
            comp->ofst += comp->max + 1;
            comp->max = 0;
            comp->tmpref = 0;
        }
        distance = number - comp->tmpref;
        comp->max = (comp->max > distance) ? comp->max : distance;
        time += sfmpv_Nfrm2Pts(comp->ofst + distance, rate);
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
void sfmpv_CalcRepeatField(SfdPly *player, M2vPicAtr *pic, int newGop) {
    SfdTim *timer = &player->tim;
    SfdFieldEntry *fields = timer->fields;
    SfdMpv *mpv = player->trn[2].hn.mpv;
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

void FUN_002a54d0(SfdPly *player, SfdSlot *slot) {
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

void sfmpv_ReformTc(SfdPly *player, M2vPicAtr *pic, long long a, int b) {
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

int sfmpv_DetectTcErr(SfdPly *player, M2vPicAtr *pic) {
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

void sfmpv_DoReformTc(SfdPly *player, M2vPicAtr *pic, long long id, int flag)
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
        if (player->see.rec == 0) {
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

void sfmpv_SetHeadTtu(SfdPly *player, M2vPicAtr *pic)
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

void sfmpv_SetDecTtu(SfdPly *player, M2vPicAtr *pic)
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

int sfmpv_FirstPicAtr(SfdPly *player, void *sj, M2vPicAtr *pic, SfdSjChunk *chunk)
{
    SfdMvInf *geom = &player->mvInf;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    int pts;
    int x, y, z;
    int n;
    if (geom->bitRate != 0)
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

void sfmpv_SetMpvHd(SfdPly *player, int pts, SfdSjChunk *chunk)
{
    SfdRecVideo *picture;
    SfdUserData *user;
    int len;
    SfdTim *timer;
    picture = sfmpv_GetHd(player);
    if (picture == 0 || picture->valid != 0)
        return;
    len = chunk->len;
    user = &picture->user;
    if (len > 512)
        len = 512;
    timer = &player->tim;
    user->size = len;
    MEM_Copy(user->data, chunk->data, len);
    if (pts == 0x3FFFF) {
        picture->time = 0;
        picture->unit = 0;
    } else {
        picture->unit = 1;
        picture->time = pts * 50;
    }
    picture->stamp = timer->state;
    picture->valid = 1;
}

void sfmpv_SetMvInf(SfdMvInf *geom, int pts, M2vPicAtr *pic, int x) {
    /* matching construct: statement-order sweep — pic->frame_rate_code is read before the copies */
    int fifth = pic->frame_rate_code;
    geom->width = pic->horizontal_size;
    geom->height = pic->vertical_size;
    geom->mbWidth = pic->mb_width;
    geom->mbHeight = pic->mb_height;
    geom->frameRate = fifth;
    geom->bitRate = pts;
    geom->vbvSize = x;
}

/* The pictures must fit the frame size the decoder was set up for, and its frame buffers must hold a
 * picture: a macroblock takes 1024 bytes as ARGB8888 output (format 2), 384 as YCC 4:2:0. */
int sfmpv_ChkBufSiz(SfdPly *player, SfdMvInf *geom) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdMpvCond *cond = &mpv->cond;
    int fmt = player->cre.bufFmt;
    int count = cond->count;
    unsigned int frmsize;
    int buf;
    int i;
    int mbw, mbh;
    int bufmbw, bufmbh;

    if (cond->max_width * cond->max_height < geom->width * geom->height)
        return sfd_ReportError(player, 0xFF000F17);
    mbw = geom->width / 16;
    mbh = geom->height / 16;
    frmsize = (fmt == 2 ? mbw * mbh * 1024 : mbw * mbh * 384) + 64;
    bufmbw = cond->frm_width / 16;
    bufmbh = cond->frm_height / 16;
    if ((fmt == 2 ? bufmbw * bufmbh * 1024 : bufmbw * bufmbh * 384) + 64 < frmsize)
        return sfd_ReportError(player, 0xFF000F18);
    buf = cond->ta_adr;
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

int sfmpv_IsConcatTimeFix(SfdPly *player) {
    return player->tim.tally.total >= 0;
}

int sfmpv_IsSkip(SfdPly *player, SfdSjChunk *chunk) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    M2vPicAtr *pic = &mpv->pic;
    int skip;
    int busy;
    unsigned int type;
    if (SFSET_GetCond(player, 47) == 1)
        return 1;
    if (SFSET_GetCond(player, 39) == 1)
        return 0;
    if (pic->field_964 != 0)
        return mpv->skipret;
    type = pic->picture_coding_type;
    busy = sfmpv_IsSeekSkip(player);
    skip = 1;
    if (busy == 0 && sfmpv_IsPtypeSkip(player, type) == 0 && sfmpv_IsEmptySkip(player, type, chunk) == 0
        && sfmpv_IsDefect(player, type) == 0)
        skip = sfmpv_IsLate(player, type) != 0;
    sfmpv_UpdateDefect(player, pic, skip);
    return skip;
}

int sfmpv_IsDefect(SfdPly *player, int kind) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    unsigned int mode = mpv->picstat;
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

void sfmpv_UpdateDefect(SfdPly *player, M2vPicAtr *pic, int kind)
{
    SfdMpv *mpv = player->trn[2].hn.mpv;
    void *handle = mpv->handle;
    int mode = mpv->picstat;
    int a, b;
    if (mpv->newgop != 0) {
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
    mpv->picstat = mode;
}

int sfmpv_IsSeekSkip(SfdPly *player) {
    SfdRecSub *link = &player->see.sub;
    SfdTimeRec *cur = &player->tim.cur;
    SfdTimeRec *f280 = &player->tim.vofst;
    if (link->time < 0) {
        return 0;
    }
    if (f280->valid != 0) {
        return 0;
    }
    return UTY_CmpTime(link->time, link->unit, cur->time, cur->unit) == 0;
}

int sfmpv_IsPtypeSkip(SfdPly *player, unsigned int kind) {
    int *pending = player->cond;
    int value;
    switch (kind) {
    case 1:
        value = pending[2];
        break;
    case 2:
        value = pending[3];
        break;
    case 3:
        value = pending[4];
        break;
    default:
        return 1;
    }
    return value == 0;
}


int sfmpv_IsEmptySkip(SfdPly *player, unsigned int type, SfdSjChunk *chunk) {
    SfdPlyInf *dec;
    SfdMvInf *geom;
    int r;

    if (SFSET_GetCond(player, 7) != 0) {
        return 0;
    }
    geom = &player->mvInf;
    dec = &player->plyInf;
    if (type == 3) {
        r = MPV_IsEmptyBpic((unsigned char *)chunk->data, chunk->len, geom->mbWidth * geom->mbHeight);
        if (r != 0) {
            dec->numSkipEmptyB++;
        }
    } else if (type == 2) {
        r = MPV_IsEmptyPpic((unsigned char *)chunk->data, chunk->len, geom->mbWidth * geom->mbHeight);
        if (r != 0) {
            dec->numSkipEmptyP++;
        }
    } else {
        r = 0;
    }
    return r;
}

/* Whether the picture would be shown late: the timer's skip hook decides when one is set, otherwise
 * its display time against the current time, within the allowed number of skips. */
int sfmpv_IsLate(SfdPly *player, unsigned int type) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
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
    if (SFTIM_GetSpeed(player) <= 1000 && mpv->nskip >= player->cond[38]) {
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
    mpv->nskip++;
    return 1;
}

void sfmpv_GetDtime(SfdPly *player, int unused, int *first, int *second) {
    int *pending = player->cond;
    *second = pending[43];
    *first = pending[42];
}

int sfmpv_SkipFrm(SfdPly *player, SfdSj *sj)
{
    SfdMpv *mpv = player->trn[2].hn.mpv;
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
        mpv->skipret = 1;
    SFPLY_AddSkipPic(player, 1, pic->picture_coding_type);
    return 0;
}

void sfmpv_SetSkipTtu(SfdPly *player) {
    SfdTimeRec *current = &player->tim.cur;
    SfdTimeRec *latest = &player->tim.latest;
    if (current->time < player->tim.vofst.time) {
        *latest = *current;
    }
}

/* takes the frame the picture is decoded into and the reference planes it predicts from */
int sfmpv_SetFrmPara(SfdPly *player, M2vPicAtr *pic, SfdFrmPara *para, SfdSlot **out) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdPlyInf *decode = &player->plyInf;
    SfdPlanes *planes;
    int columns;
    int rows;
    int lumaBlocks;
    int chromaBlocks;
    int lumaSize;
    int chromaSize;

    if (mpv->pendfrm != 0) {
        *out = mpv->pendfrm;
    } else {
        *out = SFMPVF_AllocFrm(player);
        if (*out == 0) {
            decode->noFreeFrm = 1;
            return -1;
        }
    }
    (*out)->info = *pic;
    (*out)->pts = mpv->pts;
    if (player->cre.bufFmt == 3) {
        if ((pic->picture_coding_type == 1 || pic->picture_coding_type == 2) && mpv->pendfrm == 0) {
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
            mpv->refidx_fwd ^= 1;
            mpv->refidx_bwd ^= 1;
            mpv->second = *out;
        }
        planes = mpv->planes;
        para->ref[0] = planes[mpv->refidx_fwd];
        para->ref[1] = planes[mpv->refidx_bwd];
    }
    para->dst = (*out)->buf;
    para->pic = &(*out)->info;
    para->nfrm = 0;
    para->nbyte = 0;
    decode->noFreeFrm = 0;
    return 0;
}

void FUN_002a6ea0(SfdPly *player, SfdMpv *mpv, int *out64, int *out68) {
    if (player->cre.bufFmt == 3) {
        switch (mpv->pic.picture_coding_type) {
        case 1: /* matching construct: manual — explicit single-layer case shapes the compare tree */
            break;
        case 2:
            *out64 = mpv->first->errcnt;
            *out68 = mpv->first->rcvcnt;
            return;
        case 3:
            *out64 = mpv->first->errcnt + mpv->second->errcnt;
            *out68 = mpv->first->rcvcnt + mpv->second->rcvcnt;
            return;
        }
    }
    *out64 = 0;
    *out68 = 0;
}

void sfmpv_SetStartTtu(SfdPly *player)
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

void FUN_002a7040(SfdPly *player, SfdSlot *slot) {
    slot->stamp = player->tim.cur;
    if (SFMPVP_IsSceMpegUsed(player) != 0) {
        slot->frmcnt = SFMPVP_GetFrameCount(player);
    }
    sfmpv_SetFrmTime(player, slot);
}

void sfmpv_SetFrmTime(SfdPly *player, SfdSlot *slot) {
    SfdTim *timer = &player->tim;
    SfdTimeRec *in = &slot->stamp;
    int t;
    slot->tunit = in->unit;
    slot->ftime = in->time - player->tim.vofst.time + timer->tally.total;
    slot->time_per_file = in->time;
    slot->cat_time = in->time + timer->tally.total;
    if (SFMPVP_IsSceMpegUsed(player) != 0) {
        t = UTY_MulDiv(slot->tunit, (slot->frmcnt - timer->concat_frmcnt) * 1000, SFTIM_prate[slot->info.frame_rate_code]);
        slot->time_per_file = t;
        slot->ftime = slot->cat_time = t + timer->tally.total;
    }
    if (timer->dec_time < slot->ftime) {
        timer->dec_time = slot->ftime;
        timer->dec_unit = slot->tunit;
    }
}

void FUN_002a71d0(SfdPly *player, SfdSlot *slot, void *source) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    int kind;
    char *data;
    int size;
    if ((unsigned int)(slot->info.picture_coding_type - 1) < 2) {
        FUN_002a73f0(&mpv->pool.slot[1], slot->blob);
    }
    FUN_002a7278(source, &kind, &data, &size);
    if (kind == 3) {
        memcpy(slot->blob->data, data, size);
        slot->blob->len = size;
    } else {
        FUN_002a73f0(slot->blob, &mpv->pool.slot[1]);
    }
}

void FUN_002a7278(SfdSj *source, int *kind, char **data, int *size) {
    SfdSjChunk chunk;
    char *seq;
    char *pic;
    char *ext;
    int rest;

    *kind = 0;
    *data = 0;
    *size = 0;
    source->vtbl->getChunk(source, 1, 0x7FFFFFFF, &chunk);
    seq = MPV_SearchDelim(chunk.data, chunk.len, 204);
    if (seq == 0) {
        DAT_004beb0c++;
    } else {
        if ((MPV_CheckDelim(seq) & 4) != 0) {
            if (chunk.len < seq - chunk.data + 6) {
                DAT_004beb0c++;
            } else {
                *kind = DAT_004f4e70[(seq[5] >> 3) & 7];
                if (*kind == 3) {
                    rest = chunk.data - seq + chunk.len;
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
    source->vtbl->ungetChunk(source, 1, &chunk);
}

void FUN_002a73f0(SfdSjChunk *dst, SfdSjChunk *src) {
    memcpy(dst->data, src->data, src->len);
    dst->len = src->len;
}

int sfmpv_GoDdelim(SfdPly *player, SfdSj *sj, int mask)
{
    SfdBufStat area;
    SfdDelim code;
    char *p;
    int n;
    int i;
    int found;
    int c;
    if (SFBUF_RingGetRead(player, player->trn[2].bufIn, &area) != 0)
        return 0;
    if (area.ck0.len == 0)
        return 0;
    p = sfmpv_SearchDelim(&area, mask, &code);
    if (p == 0) {
        n = area.ck0.len + area.ck1.len - 3;
        if (n < 0)
            n = 0;
    } else if (p >= area.ck0.data && p < area.ck0.data + area.ck0.len)
        n = p - area.ck0.data;
    else if (p >= area.ck1.data && p < area.ck1.data + area.ck1.len)
        n = p - area.ck1.data + area.ck0.len;
    else
        n = 0;
    sfmpv_RingAddRead(player, n);
    found = 0;
    for (i = 0; i < (n < 4 ? n : 3); i++) {
        if (i < area.ck0.len)
            c = area.ck0.data[i];
        else
            c = area.ck1.data[i - area.ck0.len];
        if (c != 0) {
            found = 1;
            break;
        }
    }
    if (found)
        player->plyInf.vidSkip += n;
    player->plyInf.vidByte += n;
    return n;
}

/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void sfmpv_RingAddRead(SfdPly *player, int n)
{
    SFBUF_RingAddRead(player, player->trn[2].bufIn, n);
    EMPTY_MACRO();
}

void sfmpv_UpdateFlowCnt(SfdPly *player) {
    SfdSj *entry;
    int a;
    int b;
    SFBUF_RingGetSj(player, player->trn[2].bufIn, &entry);
    if (entry != 0) {
        sfbuf_GetSjPos(entry, &a, &b);
        player->plyInf.vidFlow = sfbuf_MergeTotal(player->plyInf.vidFlow, a);
    }
}

int SFMPV_Create(SfdPly *player)
{
    SfdMpv *mpv = &player->mpv;
    void *dec;
    int ret;
    ret = SFSET_GetCond(player, 5);
    if (ret == 0)
        return ret;
    player->trn[2].hn.mpv = mpv;
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
    MPV_SetCond(dec, 6, player->cre.bufFmt);
    mpv->handle = dec;
    if (SFPLY_GetResetFlg() != 0)
        sfmpv_SetPicUsrBuf(player, sfmpv_picusr_pbuf, sfmpv_picusr_bufnum, sfmpv_picusr_buf1siz);
    return 0;
}

int sfmpv_InitInf(SfdPly *player, SfdMpv *mpv) {
    int i;

    if (sfmpv_CheckMpvPara() != 0) {
        return sfd_ReportError(0, 0xFF000F15);
    }
    mpv->cond = sfmpv_para;
    mpv->work = sfmpv_rfb_adr_tbl;
    mpv->bufs = sfmpv_ta_adr_tbl;
    mpv->picstat = 5;
    mpv->dlmmask = 192;
    mpv->refidx_bwd = 1;
    mpv->handle = 0;
    mpv->current = 0;
    mpv->refidx_fwd = 0;
    mpv->termflg = 0;
    mpv->gopstat = 0;
    mpv->first = 0;
    mpv->second = 0;
    mpv->pendfrm = 0;
    mpv->skipret = 0;
    mpv->dlmwait = 0;
    mpv->tmpref_adj = 0;
    sfmpv_InitFrmObj(mpv->slots, mpv->bufs.w, 16);
    mpv->nskip = 0;
    mpv->nconcat = 0;
    sfmpv_InitPicAtr(&mpv->pic);
    mpv->last_ngop = -1;
    mpv->newgop = 0;
    mpv->limit = 0x7FFFFFFF;
    sfmpv_InitComplementPts(&mpv->ptscomp);
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
    if (sfmpv_para.rfb_adr == 0 || sfmpv_para.ta_adr == 0) {
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
            slot->ftime = 0;
            slot->tunit = 1;
            slot->errcnt = 0;
            slot->rcvcnt = 0;
            slot->concat_cnt = 0;
            slot->time_per_file = 0;
            slot->cat_time = 0;
            sfmpv_InitPicAtr(&slot->info);
            slot->frmcnt = 0;
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
    pool->slot[0].data = 0;
    pool->slot[0].len = 0;
    pool->slot[1].data = 0;
    pool->slot[1].len = 0;
    for (i = 0; i < 16; i++) {
        pool->slot[i + 2].data = 0;
        pool->slot[i + 2].len = 0;
    }
}

void sfmpv_ErrFn(SfdPly *player, int code) {
    if (code < -3 || (code >= -1 && code != 0)) {
        sfd_ReportError(player, code);
    }
}

int SFMPV_Destroy(SfdPly *player)
{
    SfdMpv *mpv = player->trn[2].hn.mpv;
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

void SFMPV_GetWrite(SfdPly *player) {
    sfd_ReportError(player, 0xFF000F0D);
}

void SFMPV_AddWrite(SfdPly *player) {
    sfd_ReportError(player, 0xFF000F0D);
}

int SFMPV_GetRead(SfdPly *player, SfdFrameInfo **out) {
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
    timer->base = (*out)->time;
    timer->base_frames = (*out)->unit;
    return 0;
}

/* matching construct: placement — declared here; with the other declarations it changes the
 * address-taken local loads of sfmpv_SetDecTtu */
SfdVfrm *SFMPVF_SearchVfrmData(SfdPly *player, SfdSlot *target);

/* fills the frame information handed to the application from the frame's slot and marks its record
 * in use */
void sfmpv_SetFrmInf(SfdPly *player, SfdSlot *slot, SfdFrameInfo **out) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    M2vPicAtr *pic = &slot->info;
    SfdVfrm *record;

    record = SFMPVF_SearchVfrmData(player, slot);
    *out = &record->inf;
    record->used = 1;
    mpv->current = slot;
    (*out)->width = pic->horizontal_size;
    (*out)->height = pic->vertical_size;
    (*out)->x_mb = pic->mb_width;
    (*out)->y_mb = pic->mb_height;
    (*out)->picType = pic->picture_coding_type;
    (*out)->time = slot->ftime;
    (*out)->unit = slot->tunit;
    (*out)->bufFmt = player->cre.bufFmt;
    (*out)->buf = slot->buf;
    (*out)->errcnt = slot->errcnt;
    (*out)->rcvcnt = slot->rcvcnt;
    (*out)->concat_cnt = slot->concat_cnt;
    (*out)->time_per_file = slot->time_per_file;
    (*out)->cat_time = slot->cat_time;
    (*out)->picUsr = slot->blob;
    (*out)->f60 = pic->f64;
    (*out)->f64 = pic->f68;
    if (pic->f64 == 0) {
        (*out)->tail.detail.f72 = 2;
    } else {
        (*out)->tail.detail.f72 = 1;
    }
    (*out)->tail.detail.pts = slot->pts;
    (*out)->tail.detail.picture_structure = pic->picture_structure;
    (*out)->tail.detail.chroma_format = pic->chroma_format;
    (*out)->tail.detail.bit_rate = pic->bit_rate;
    (*out)->tail.detail.vbv_buffer_size = pic->vbv_buffer_size;
    (*out)->tail.detail.display_horizontal_size = pic->display_horizontal_size;
    (*out)->tail.detail.display_vertical_size = pic->display_vertical_size;
    (*out)->tail.detail.progressive_frame = pic->progressive_frame;
    (*out)->tail.detail.top_field_first = pic->top_field_first;
    (*out)->tail.detail.repeat_first_field = pic->repeat_first_field;
    (*out)->tail.detail.aspect_ratio_information = pic->aspect_ratio_information;
    (*out)->tail.detail.constrained_parameters_flag = pic->constrained_parameters_flag;
    (*out)->tail.detail.frame_rate_extension_n = pic->frame_rate_extension_n;
    (*out)->tail.detail.frame_rate_extension_d = pic->frame_rate_extension_d;
    (*out)->tail.detail.profile_and_level_indication = pic->profile_and_level_indication;
    (*out)->tail.detail.progressive_sequence = pic->progressive_sequence;
    (*out)->tail.detail.low_delay = pic->low_delay;
    (*out)->tail.detail.video_format = pic->video_format;
    (*out)->tail.detail.colour_description = pic->colour_description;
    (*out)->tail.detail.colour_primaries = pic->colour_primaries;
    (*out)->tail.detail.transfer_characteristics = pic->transfer_characteristics;
    (*out)->tail.detail.matrix_coefficients = pic->matrix_coefficients;
}

int SFMPV_AddRead(SfdPly *player, char *body) {
    char guard[16];
    int result;
    sfd_Lock(guard);
    result = sfmpv_AddReadSub(player, body);
    sfd_Unlock(guard);
    return result;
}

int sfmpv_AddReadSub(SfdPly *player, char *body) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdVfrm *record = FUN_002a8158(player, body);
    SfdSlot *found;
    SfdSlot *current;
    if (record->used != 1) {
        return sfd_ReportError(player, 0xFF000F0E);
    }
    found = SFMPVF_SearchFrmObj(player, body);
    current = mpv->current;
    if (current != found) {
        return sfd_ReportError(player, 0xFF000F0F);
    }
    record->used = 0;
    SFMPVF_EndDrawFrm(current);
    return 0;
}

SfdVfrm *FUN_002a8158(SfdPly *player, char *body) {
    return (SfdVfrm *)(body - offsetof(SfdVfrm, inf));
}

int SFMPV_Seek(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    int flag[4];
    int ready;
    int status;
    status = sfmpv_ReprocessShc(player, mpv, flag);
    if (status != 0) {
        return status;
    }
    ready = flag[0];
    mpv->picstat = 2;
    if (ready == 0 || SFSET_GetCond(player, 48) == 0) {
        mpv->dlmmask = 192;
    } else {
        mpv->dlmmask = 200;
    }
    return 0;
}

int sfmpv_ReprocessShc(SfdPly *player, SfdMpv *mpv, int *ok)
{
    SfdRecVideo *picture;
    SfdSjChunk chunk;
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
    chunk.data = user->data;
    chunk.len = user->size;
    if (MPV_DecodePicAtr(mpv->handle, &chunk, out) != 0)
        return sfd_ReportError(player, 0xFF000F1B);
    *ok = 1;
    return 0;
}

SfdRecVideo *sfmpv_GetHd(SfdPly *player) {
    SfdRec *work = player->see.rec;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    if (work == 0) {
        return 0;
    }
    if (mpv->nconcat > 0) {
        return 0;
    }
    return &work->video;
}

void SFD_LockFrm(SfdPly *player, char *body) {
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
    player->plyInf.lockCnt++;
}

void SFD_UnlockFrm(SfdPly *player, char *body) {
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
        player->plyInf.lockCnt--;
    }
}

SfdSlot *SFMPVF_SearchFrmObj(SfdPly *player, char *body) {
    SfdVfrm *record = player->vfrm;
    SfdMpv *mpv = player->trn[2].hn.mpv;
    SfdSlot *slot = mpv->slots;
    int i;
    for (i = 0; i < 16; i++) {
        if ((char *)&record->inf == body) {
            return slot;
        }
        record++;
        slot++;
    }
    return 0;
}

SfdVfrm *SFMPVF_SearchVfrmData(SfdPly *player, SfdSlot *target) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    int i = 0;
    int count = mpv->slotCount;
    SfdSlot *slot = mpv->slots;
    SfdVfrm *record;
    if (count > 0) {
        record = player->vfrm;
        do {
            /* matching construct: hand — the candidate is taken before the
               advance, so the compare sits in the copy's delay slot */
            SfdVfrm *found = record;
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

void SFMPVF_TermDec(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    mpv->termflg = 1;
}

int SFMPVF_IsTermDec(SfdPly *player) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    return mpv->termflg;
}

SfdMpv *SFMPVF_SetGopStat(SfdPly *player, int value) {
    SfdMpv *mpv = player->trn[2].hn.mpv;
    mpv->gopstat = value;
    return mpv;
}

int SFMPVF_GetNumFrm(SfdPly *player) {
    char guard[16];
    SfdMpv *mpv;
    SfdSlot *slot;
    int count;
    int i;
    int n;
    sfd_Lock(guard);
    mpv = player->trn[2].hn.mpv;
    count = 0;
    slot = mpv->slots;
    n = mpv->slotCount;
    for (i = 0; i < n; i++) {
        if (slot->state == 2 || slot->state == 4) {
            count++;
        }
        slot++;
    }
    if (mpv->termflg == 1 && count == 0) {
        count = -1;
    }
    sfd_Unlock(guard);
    return count;
}

SfdSlot *SFMPVF_AllocFrm(SfdPly *player) {
    char guard[16];
    SfdMpv *mpv;
    SfdSlot *slot;
    int i;
    int n;
    sfd_Lock(guard);
    mpv = player->trn[2].hn.mpv;
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

SfdSlot *SFMPVF_HoldFrm(SfdPly *player, int *out) {
    int c;
    SfdSlot *best = 0;
    int n = 0;
    SfdMpv *mpv;
    SfdSlot *slot;
    int i, cnt;
    sfd_Lock(&c);
    mpv = player->trn[2].hn.mpv;
    cnt = mpv->slotCount;
    slot = mpv->slots;
    *out = 0;
    for (i = 0; i < cnt; i++, slot++) {
        if (slot->state == 2 || slot->state == 4) {
            if (sfmpvf_IsChkFirst(best, slot) != 0) best = slot;
            n++;
        }
    }
    if (n == 1 && mpv->termflg != 0) *out = n;
    sfd_Unlock(&c);
    return best;
}

void SFD_GetNextPicUsr(void *sfd, char **data, int *size) {
    SfdPly *player = sfd;
    SfdSlot *slot = sfmpvf_ReferNextFrmReady(player);
    SfdSjChunk *chunk;
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
    *data = chunk->data;
    *size = chunk->len;
}

int SFD_GetNumRemainFrm(void *sfd) {
    SfdPly *player = sfd;
    int refused;
    int count;
    refused = SFLIB_CheckHn(player);
    if (refused != 0) {
        sfd_ReportError(0, 0xFF000187);
        return 0;
    }
    count = FUN_002a8878(player);
    if (player->plyInf.frmOut == 1 && count > 0) {
        count--;
    }
    return count;
}

int FUN_002a8878(SfdPly *player) {
    int c;
    SfdSlot *p, *q;
    int k, r;
    sfd_Lock(&c);
    sfmpvf_SearchStbyFrm(player, &p, &q);
    if (player->stat != 4) q = 0;
    k = SFSET_GetCond(player, 15);
    if (p != 0 && (k == 0 || SFTIM_IsGetFrmTimeTunit(player, p->ftime, p->tunit) != 0)) {
        if (q != 0 && (k == 0 || SFTIM_IsGetFrmTimeTunit(player, q->ftime, q->tunit) != 0)) {
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
    SfdPly *player = sfd;
    if (SFLIB_CheckHn(player) != 0) {
        sfd_ReportError(0, 0xFF000183);
        return 0;
    }
    return sfmpvf_ReferNextFrmReady(player) != 0;
}

SfdSlot *sfmpvf_ReferNextFrmReady(SfdPly *player) {
    int guard;
    SfdSlot *best;
    SfdSlot *second;
    sfd_Lock(&guard);
    if (player->stat != 4) {
        second = 0;
    } else {
        sfmpvf_SearchStbyFrm(player, &best, &second);
        if (second != 0 && SFSET_GetCond(player, 15) != 0) {
            if (SFTIM_IsGetFrmTimeTunit(player, second->ftime, second->tunit) == 0) {
                second = 0;
            }
        }
    }
    sfd_Unlock(&guard);
    return second;
}

void sfmpvf_SearchStbyFrm(SfdPly *player, SfdSlot **best, SfdSlot **second) {
    SfdMpv *mpv;
    SfdSlot *slot;
    int held = 0;
    int i;
    int n;
    mpv = player->trn[2].hn.mpv;
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
        result = a->ftime > b->ftime;
    }
    return result;
}
