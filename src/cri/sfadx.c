#include "dw4/cri/sj.h"
#include "dw4/cri/mcp.h"
#include <string.h>
#include <math.h>
#include "dw4/cri/mps.h"
#include "dw4/cri/uty.h"
#include "dw4/cri/sfd.h"
#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/sfdply.h"

/* kept here: with this declaration in sfd.h, sfmpv.c (which includes it) schedules sfmpv_SetDecTtu differently */
extern int sfadxt_stat;

extern char sfadx_silent_block[];
extern SfdAdxCfg sfadxt_para;
extern int sfadxt_adxterr;
extern AdxtObj *sfadxt_save_hn;


void SFADXT_SetOutPan(SfdPly *h, int ch, int pan);
int SFADXT_GetOutPan(SfdPly *h, int ch);
void SFADXT_SetOutVol(SfdPly *h, int vol);
int SFADXT_GetOutVol(SfdPly *h);
void SFADXT_SetSpeed(SfdPly *h, int volume);
void sfadxt_HeadDecCallBack(SfdPly *h);
int sfadxt_ExecServerSub(SfdPly *h);
void FUN_0029b788(SfdPly *h);
int sfadxt_SupplyData(SfdPly *h, int *out);
void sfadxt_GetFreeChunk(SfdSj *sj, int n, SfdSjChunk *ck);
void sfadxt_PutDataChunk(SfdSj *sj, int len, SfdSjChunk *ck);
void sfadxt_CopyData(SfdPly *h, char *dst, int max, int *out);
void sfadxt_AdjustSync(SfdPly *h, char *buf, int size, int *used);
int sfadxt_AdjDiscard(char *records, int length, int *found);
int sfadxt_InsertSilence(SfdPly *h, int nch, int size);
void sfadxt_ExcludeHdr(SfdPly *h, char *buf, int size, int *used);
char *sfadxt_SearchAlign(SfdPly *h, char *buf, int size);
void sfadxt_ExcludeSilence(SfdPly *h, char *buf, int size, int *used);
int sfadxt_GetNchSfreq(SfdPly *h, int *out12, int *out16);
void sfadxt_ChkPrepFlg(SfdPly *h);
int sfadxt_IsPrepEnd(SfdPly *h);
void sfadxt_ChkTermFlg(SfdPly *h, int flag);
int sfadxt_RingGetRead(SfdPly *h, char **addr, int *size);
int sfadxt_RingAddRead(SfdPly *h, int n);
void sfadxt_UpdateFlowCnt(SfdPly *h);
int sfadxt_GetTermSrc(SfdPly *h);
int sfadxt_GetTermDst(SfdPly *h);
void sfadxt_SetTermDst(SfdPly *h, int value);
void sfadxt_SetAdxtHd(SfdPly *h);
int sfadxt_IsEndDecinfo(AdxtObj *adxt);
void sfadxt_SetSvrFreq(SfdPly *h);
int sfadxt_InitInf(SfdPly *h, SfdAdxCtx *ctx);
int SFADXT_Create(SfdPly *h);
AdxtObj *sfadxt_CreateEx(SfdAdxCfg *cfg);
AdxtObj *sfadxt_RestoreAdxtHn(void);
void sfadxt_SetTimeFn(SfdPly *h);
int sfadxt_GetTime(void *sfd, int *time, int *unit);
void sfadxt_GetTimeTst(void *blk, AdxtObj *adxt, int *out0, int *out1);
int sfadxt_DestroySub(AdxtObj *adxt);
int sfadxt_SaveAdxtHn(AdxtObj *adxt);
int SFADXT_Stop(SfdPly *h);
void sfadxt_WaitStart(SfdPly *h, int value);
void sfadxt_DoPause(SfdPly *h, int value);
void sfadxt_WtPause();
void sfadxt_GetTimeOneFrmAudio(void *blk, int *result, int target);
SfdRecAudio *sfadxt_GetHd(SfdPly *h);

int SFADXT_IsHeader(unsigned char *header, int length, int *headerSize) {
    *headerSize = 288;
    if (length < 288) {
        return 0;
    }
    if (header[0] != 0x80) {
        return 0;
    }
    if (header[1] != 0) {
        return 0;
    }
    return strncmp(header + 282, "(c)CRI", 6) == 0;
}

int SFADXT_IsEndcode(unsigned char *header, int length, int *headerSize) {
    *headerSize = 18;
    if (length < 18) {
        return 0;
    }
    if (header[0] != 0x80) {
        return 0;
    }
    return header[1] == 1;
}

void SFADXT_SetOutPan(SfdPly *h, int ch, int pan) {
    ADXT_SetOutPan(h->trn[3].hn.adxt->adxt, ch, pan);
}

int SFADXT_GetOutPan(SfdPly *h, int ch) {
    return ADXT_GetOutPan(h->trn[3].hn.adxt->adxt, ch);
}

void SFADXT_SetOutVol(SfdPly *h, int vol) {
    ADXT_SetOutVol(h->trn[3].hn.adxt->adxt, vol);
}

int SFADXT_GetOutVol(SfdPly *h) {
    return ADXT_GetOutVol(h->trn[3].hn.adxt->adxt);
}

void SFADXT_SetSpeed(SfdPly *h, int volume) {
    AdxtObj *adxt = h->trn[3].hn.adxt->adxt;
    int hi;
    int lo;
    float t;
    if (adxt == 0) {
        return;
    }
    if (volume == 1000) {
        hi = 0;
        lo = 0;
    } else {
        t = (logf(volume) - 6.907755f) * 1731.23401f;
        hi = t * 0.01f;
        lo = (int)t - hi * 100;
    }
    ADXT_SetTranspose(adxt, hi, lo);
    return;
}

void SFD_SetAdxtPara(SfdAdxCfg *cfg) {
    sfadxt_para.bsize = cfg->bsize;
    sfadxt_para.buf = (char *)(((int)cfg->buf + 31) & ~31);
    sfadxt_para.xsize = cfg->xsize;
    sfadxt_para.maxnch = cfg->maxnch;
    sfadxt_para.work = (char *)(((int)cfg->work + 31) & ~31);
    sfadxt_para.f16 = cfg->f16;
    sfadxt_para.worksize = cfg->worksize;
}

int SFADXT_Init(void) {
    ADXT_Init();
    SFA_Init();
    UTY_MemsetDword(&sfadxt_para, 0, 7);
    return 0;
}

int SFADXT_Finish(void) {
    SFA_Finish();
    ADXT_Finish();
    return 0;
}

void sfadxt_HeadDecCallBack(SfdPly *h) {
    SfdTim *tim = &h->tim;
    AdxtObj *adxt = h->trn[3].hn.adxt->adxt;
    int w;
    int ht;
    if (tim->queue.wr == tim->queue.rd) {
        w = ADXT_GetNumSmpl(adxt);
        ht = ADXT_GetSfreq(adxt);
        if (w > 0 && ht > 0) {
            SFCON_WriteTotSmplQue(h, w, ht);
            return;
        }
    }
}

void SFADXT_ExecServer(SfdPly *h) {
    sfadxt_ExecServerSub(h);
}

int sfadxt_ExecServerSub(SfdPly *h) {
    int out;
    int r;
    if (SFSET_GetCond(h, SFD_COND_AUDIO) == 0) {
        return 0;
    }
    if (sfadxt_GetTermDst(h) == 1) {
        return 0;
    }
    FUN_0029b788(h);
    r = sfadxt_SupplyData(h, &out);
    sfadxt_ChkPrepFlg(h);
    sfadxt_ChkTermFlg(h, out);
    sfadxt_SetAdxtHd(h);
    sfadxt_SetSvrFreq(h);
    sfadxt_HeadDecCallBack(h);
    return r;
}

void FUN_0029b788(SfdPly *h) {
}

/* matching construct: permuter, reduced by hand: the field read as an int and cast to the handler */
int sfadxt_SupplyData(SfdPly *h, int *out) {
    char *addr;
    int size;
    int result;
    SfdAdxCtx *ctx;
    int ret;
    *out = 0;
    ctx = h->trn[3].hn.adxt;
    if ((ret = sfadxt_RingGetRead(h, &addr, &size)) != 0)
        return ret;
    *out = size;
    ctx->step(h, addr, size, &result);
    if ((ret = sfadxt_RingAddRead(h, result)) != 0)
        return ret;
    sfadxt_UpdateFlowCnt(h);
    return 0;
}

void sfadxt_GetFreeChunk(SfdSj *sj, int n, SfdSjChunk *ck) {
    sj->vtbl->getChunk(sj, 0, n, ck);
}

void sfadxt_PutDataChunk(SfdSj *sj, int len, SfdSjChunk *ck) {
    SfdSjChunk rest;
    if (len == 0) {
        sj->vtbl->ungetChunk(sj, 0, ck);
        return;
    }
    SJ_SplitChunk(ck, len, ck, &rest);
    sj->vtbl->putChunk(sj, 1, ck);
    sj->vtbl->ungetChunk(sj, 0, &rest);
}

void sfadxt_CopyData(SfdPly *h, char *dst, int max, int *out) {
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    SfdSj *sj = ctx->sj;
    SfdSjChunk ck;
    int n;
    sfadxt_GetFreeChunk(sj, ctx->cfg.bsize, &ck);
    n = ck.len;
    if (max < n)
        n = max;
    if (n > 0x19000)
        n = 0x19000;
    MEM_Copy(ck.data, dst, n);
    sfadxt_PutDataChunk(sj, n, &ck);
    ctx->total += n;
    *out = n;
}

/* the ADX step that keeps the decode position in step with the ring: feeds up to the whole 18-byte
 * records the ring still lacks, backs off when it is ahead, and hands over to the plain copy step at the
 * end of the stream */
void sfadxt_AdjustSync(SfdPly *h, char *buf, int size, int *used) {
    SfdTim *ring = &h->tim;
    SfdAdxCtx *ctx;
    int nch;
    int rate;
    int atEnd;
    int found;
    int footer;
    int lo;
    int hi;
    int diff;
    int result;
    int total;
    int chunk;
    int back;
    int r;
    *used = 0;
    ctx = h->trn[3].hn.adxt;
    if (sfadxt_GetNchSfreq(h, &nch, &rate) != 0) {
        ctx->step = sfadxt_CopyData;
        return;
    }
    lo = SFTIM_GetAudioStartSample(ring, rate);
    if (lo < 0)
        return;
    if (SFSET_GetCond(h, 5) == 0) {
        SFTIM_SetStartTime(ring, lo, rate);
        ctx->step = sfadxt_CopyData;
        return;
    }
    hi = SFTIM_GetVideoStartSample(ring, rate, &atEnd);
    if (hi < 0)
        return;
    result = 0;
    SFTIM_SetStartTime(ring, hi, rate);
    diff = hi - lo - ctx->pos;
    if (diff >= 0) {
        total = (diff >> 5) * nch * 18;
        found = 0;
        if (total > 0) {
            chunk = size / (nch * 18) * nch * 18;
            chunk = chunk < total ? chunk : total;
            result = sfadxt_AdjDiscard(buf, chunk, &found);
            ctx->pos += result / (nch * 18) << 5;
            total -= chunk;
        }
        if (total <= 0 && atEnd != 0) {
            ctx->step = sfadxt_CopyData;
            found = ADXT_IsEndcode(buf, size, &footer);
        }
        if (found != 0)
            SFSET_SetCond(h, 6, 0);
    } else if (atEnd != 0) {
        back = -diff;
        back = back / 32 * 32;
        if (back > 0) {
            r = sfadxt_InsertSilence(h, nch, back);
            ctx->pos -= r;
            back -= r;
        }
        if (back <= 0)
            ctx->step = sfadxt_CopyData;
    }
    *used = result;
    h->plyInf.audByte += result;
}

int sfadxt_AdjDiscard(char *records, int length, int *found) {
    int ftrlen;
    int pos;
    *found = 0;
    for (pos = 0; pos < length; pos += 18) {
        if (ADXT_IsEndcode(records, 18, &ftrlen) != 0) {
            *found = 1;
            break;
        }
        records += 18;
    }
    return pos;
}

int sfadxt_InsertSilence(SfdPly *h, int nch, int size) {
    return ADXT_InsertSilence(h->trn[3].hn.adxt->adxt, nch, size);
}

void sfadxt_ExcludeHdr(SfdPly *h, char *buf, int size, int *used) {
    SfdAdxCtx *ctx;
    int len;
    int n;
    *used = 0;
    ctx = h->trn[3].hn.adxt;
    if (size < 288)
        return;
    if (ADXT_IsHeader(buf, size, &len) != 0)
        n = len;
    else if (SFHDS_GetMuxVerNum(h) < 108)
        n = sfadxt_SearchAlign(h, buf, size) - buf;
    else
        n = 0;
    *used = n;
    ctx->step = sfadxt_AdjustSync;
    h->plyInf.audByte += n;
}

char *sfadxt_SearchAlign(SfdPly *h, char *buf, int size) {
    int ftrlen;
    char *end = buf + size;
    char *base;
    char *p;
    char *bestBase = 0;
    int found = 0;
    /* matching construct: declaration permutation — best declared after found */
    char *best = 0;
    for (base = buf; base < buf + 36; base += 2) {
        found = 0;
        for (p = base; p < end; p += 18) {
            if (*p < 0) {
                found = 1;
                if (ADXT_IsEndcode(p, 18, &ftrlen) != 0 && best < p) {
                    best = p;
                    bestBase = base;
                }
                break;
            }
        }
        if (!found)
            break;
    }
    if (found) {
        if (bestBase == 0) {
            sfd_ReportError(h, 0xFF000C0A);
            return buf;
        }
        base = bestBase;
    }
    return base;
}

void sfadxt_ExcludeSilence(SfdPly *h, char *buf, int size, int *used) {
    SfdAdxCtx *ctx;
    int pos;
    int nch;
    int rate;
    *used = 0;
    ctx = h->trn[3].hn.adxt;
    if (SFHDS_GetMuxVerNum(h) >= 108) {
        ctx->step = sfadxt_ExcludeHdr;
        return;
    }
    for (pos = 0; pos < size - 18; pos += 18) {
        if (memcmp(buf, sfadx_silent_block, 18) != 0) {
            ctx->step = sfadxt_ExcludeHdr;
            break;
        }
        buf += 18;
    }
    *used = pos;
    h->plyInf.audByte += pos;
    if (sfadxt_GetNchSfreq(h, &nch, &rate) == 0)
        ctx->pos += pos / (nch * 18) * 32;
}

int sfadxt_GetNchSfreq(SfdPly *h, int *out12, int *out16) {
    SfdRecAudio *info = sfadxt_GetHd(h);
    if (info == 0) {
        return -1;
    }
    *out12 = info->nch;
    *out16 = info->sfreq;
    return 0;
}

void sfadxt_ChkPrepFlg(SfdPly *h) {
    SfdTrnSlot *sub = &h->trn[3];
    int sidx2 = sub->bufOut[0];
    int sidx = sub->bufIn;
    if (SFBUF_GetPrepFlg(h, sidx2) != 1 && SFBUF_GetPrepFlg(h, sidx) == 1 && sfadxt_IsPrepEnd(h) != 0) {
        SFBUF_SetPrepFlg(h, sidx2, 1);
    }
}

int sfadxt_IsPrepEnd(SfdPly *h) {
    return ADXT_GetStat(h->trn[3].hn.adxt->adxt) == 3;
}

void sfadxt_ChkTermFlg(SfdPly *h, int flag) {
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    AdxtObj *adxt = ctx->adxt;
    SfdTst *blk = &h->tim.tst;
    int st;
    int err;
    st = ADXT_GetStat(adxt);
    err = ADXT_GetErrCode(adxt);
    if (err != 0)
        sfadxt_adxterr = err;
    if (SFSET_GetCond(h, 26) == 0)
        err = 0;
    switch (err) {
    case 0:
        break;
    case -1:
        sfd_ReportError(h, 0xFF000C08);
        break;
    case -2:
        sfd_ReportError(h, 0xFF000C09);
        break;
    default:
        sfd_ReportError(h, 0xFF000C07);
        break;
    }
    if (st == 4 || st == 5)
        SFTST_SetAdjFlg(blk, 0);
    if (st == 5 || err != 0)
        sfadxt_SetTermDst(h, 1);
    if (sfadxt_GetTermSrc(h) != 1 || flag != 0)
        return;
    ADXT_TermSupply(adxt);
    if (ctx->total != 0)
        return;
    sfadxt_SetTermDst(h, 1);
}

int sfadxt_RingGetRead(SfdPly *h, char **addr, int *size) {
    SfdBufStat stat;
    int ret = SFBUF_RingGetRead(h, h->trn[3].bufIn, &stat);
    *addr = stat.ck0.data;
    *size = stat.ck0.len;
    return ret;
}

int sfadxt_RingAddRead(SfdPly *h, int n) {
    int ret = SFBUF_RingAddRead(h, h->trn[3].bufIn, n);
    if (ret != 0)
        return ret;
    return 0;
}

void sfadxt_UpdateFlowCnt(SfdPly *h) {
    SfdTrnSlot *sub = &h->trn[3];
    SfdAdxCtx *other = sub->hn.adxt;
    SfdSj *entry;
    int a;
    int b;
    SFBUF_RingGetSj(h, sub->bufIn, &entry);
    if (entry != 0) {
        sfbuf_GetSjPos(entry, &a, &b);
        h->plyInf.audInWr = sfbuf_MergeTotal(h->plyInf.audInWr, a);
        h->plyInf.audInRd = sfbuf_MergeTotal(h->plyInf.audInRd, b);
        sfbuf_GetSjPos(other->sj, &a, &b);
        h->plyInf.audSjWr = sfbuf_MergeTotal(h->plyInf.audSjWr, a);
        h->plyInf.audSjRd = sfbuf_MergeTotal(h->plyInf.audSjRd, b);
    }
}

int sfadxt_GetTermSrc(SfdPly *h) {
    SFBUF_GetTermFlg(h, h->trn[3].bufIn);
}

int sfadxt_GetTermDst(SfdPly *h) {
    SFBUF_GetTermFlg(h, h->trn[3].bufOut[0]);
}

void sfadxt_SetTermDst(SfdPly *h, int value) {
    SFBUF_SetTermFlg(h, h->trn[3].bufOut[0], value);
}

void sfadxt_SetAdxtHd(SfdPly *h) {
    SfdRecAudio *info = sfadxt_GetHd(h);
    AdxtObj *adxt;
    int n;
    if (info != 0 && info->valid == 0) {
        adxt = h->trn[3].hn.adxt->adxt;
        if (sfadxt_IsEndDecinfo(adxt) != 0) {
            info->sfreq = ADXT_GetSfreq(adxt);
            info->nsmpl = ADXT_GetNumSmpl(adxt);
            info->nch = ADXT_GetNumChan(adxt);
            n = info->sfreq * info->nch * 9 / 16;
            info->unit = 1;
            info->valid = 1;
            info->time = n;
        }
    }
}

int sfadxt_IsEndDecinfo(AdxtObj *adxt) {
    if ((unsigned int)ADXT_GetStat(adxt) < 2) {
        return 0;
    }
    return 1;
}

void sfadxt_SetSvrFreq(SfdPly *h) {
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    AdxtObj *adxt = ctx->adxt;
    int value = SFSET_GetCond(h, 27);
    if (ctx->opt27 != value) {
        ctx->opt27 = value;
        ADXT_SetSvrFreq(adxt, value);
    }
}

/* creates the audio driver when audio is on (condition 6): the ADXT, the ring it reads and the output
 * interface, then starts the ADXT paused on the ring with the audio clock as time source */
int SFADXT_Create(SfdPly *h) {
    SfdAdxCtx *ctx = &h->adxt;
    SfdAdxCfg *cfg = &ctx->cfg;
    SfdAoap *iface;
    void *adxt;
    SfdSj *sj;
    int ret;

    if (SFSET_GetCond(h, SFD_COND_AUDIO) == 0) {
        return 0;
    }
    h->trn[3].hn.adxt = ctx;
    ret = sfadxt_InitInf(h, ctx);
    if (ret != 0) {
        return ret;
    }
    adxt = sfadxt_CreateEx(cfg);
    if (adxt == 0) {
        return sfd_ReportError(0, 0xFF000C04);
    }
    sj = SJRBF_Create(cfg->buf, cfg->bsize, cfg->xsize);
    if (sj == 0) {
        return sfd_ReportError(0, 0xFF000C05);
    }
    ctx->adxt = adxt;
    ctx->sj = sj;
    iface = &h->aoap;
    h->trn[7].hn.aoap = iface;
    iface->rna = (int)((AdxtObj *)adxt)->rna;
    iface->setOutPan = SFADXT_SetOutPan;
    iface->getOutPan = SFADXT_GetOutPan;
    iface->setOutVol = SFADXT_SetOutVol;
    iface->getOutVol = SFADXT_GetOutVol;
    iface->setSpeed = SFADXT_SetSpeed;
    ADXT_StartSj(adxt, sj);
    sfadxt_WaitStart(h, 1);
    sfadxt_SetTimeFn(h);
    return 0;
}

int sfadxt_InitInf(SfdPly *h, SfdAdxCtx *ctx) {
    SfdRatio pair[4];
    if (sfadxt_para.buf == 0 || sfadxt_para.work == 0)
        return sfd_ReportError(0, 0xFF000C06);
    ctx->cfg = sfadxt_para;
    ctx->adxt = 0;
    ctx->sj = 0;
    ctx->time = -1;
    ctx->unit = 1;
    ctx->f44 = 0;
    ctx->carry = 0;
    ctx->started = 0;
    ctx->pos = 0;
    ctx->step = sfadxt_CopyData;
    ctx->f64 = 0;
    ctx->opt27 = -1;
    ctx->total = 0;
    ctx->f76 = 0;
    pair[0].num = SFSET_GetCond(h, 63);
    pair[0].den = 1000000;
    pair[1].num = SFSET_GetCond(h, 64);
    pair[1].den = 1000000;
    pair[2].num = SFSET_GetCond(h, 65);
    pair[2].den = 1000000;
    pair[3].num = SFSET_GetCond(h, 66);
    pair[3].den = 1000000;
    SFTST_Create(&h->tim.tst);
    SFTST_SetTstFlg(&h->tim.tst, SFSET_GetCond(h, 72));
    SFTST_SetTolerance(&h->tim.tst, &pair[0]);
    SFTST_SetExcessErr(&h->tim.tst, &pair[1]);
    SFTST_SetAdjStart(&h->tim.tst, &pair[2]);
    SFTST_SetAdjPoff(&h->tim.tst, &pair[3]);
    SFTST_SetMovaveRange(&h->tim.tst, SFSET_GetCond(h, 62));
    UTY_InitTmr(SFSET_GetCond(h, 61));
    return 0;
}

AdxtObj *sfadxt_CreateEx(SfdAdxCfg *cfg) {
    AdxtObj *adxt;
    AdxtObj *ret;
    if (SFPLY_GetResetFlg() != 1) {
        adxt = ADXT_Create(cfg->maxnch, cfg->work, cfg->worksize);
    } else {
        adxt = sfadxt_RestoreAdxtHn();
    }
    ret = 0;
    if (adxt != 0) {
        ADXT_SetAutoRcvr(adxt, 0);
        ret = adxt;
    }
    return ret;
}

AdxtObj *sfadxt_RestoreAdxtHn(void) {
    return sfadxt_save_hn;
}

void sfadxt_SetTimeFn(SfdPly *h) {
    SFTIM_SetTimeFn(h, sfadxt_GetTime, 2);
    SFSET_SetCond(h, 15, 2);
}

int sfadxt_GetTime(void *sfd, int *time, int *unit) {
    SfdPly *h = sfd;
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    AdxtObj *adxt = ctx->adxt;
    SfdTst *blk = &h->tim.tst;
    int nowTime;
    int nowUnit;
    if (SFTIM_ChkRegularTime(h, time, unit) == 0)
        return 0;
    if (h->stat == 4) {
        sfadxt_GetTimeTst(blk, adxt, &nowTime, &nowUnit);
        if (ctx->time < nowTime) {
            /* matching construct: variant search — the unit read before the time store */
            int newUnit = nowUnit;
            ctx->time = nowTime;
            ctx->unit = newUnit;
        }
    }
    *time = ctx->time;
    *unit = ctx->unit;
    return 0;
}

void sfadxt_GetTimeTst(void *blk, AdxtObj *adxt, int *out0, int *out1) {
    SfdRatio size;
    SfdRatio extra;
    SfdRatio result;
    int width;
    int height;
    sfadxt_stat = ADXT_GetStat(adxt);
    ADXT_GetTime(adxt, &width, &height);
    size.num = width;
    size.den = height;
    extra.num = UTY_GetTmr();
    extra.den = UTY_GetTmrUnit();
    SFTST_Calc(blk, &size, &extra, &result);
    *out0 = result.num;
    *out1 = result.den;
}

int SFADXT_Destroy(SfdPly *h) {
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    AdxtObj *adxt = ctx->adxt;
    SfdSj *sj = ctx->sj;
    int ret;
    if (adxt == 0)
        return 0;
    sfadxt_para = ctx->cfg;
    if (SFPLY_GetResetFlg() != 1) {
        ret = sfadxt_DestroySub(adxt);
    } else {
        SFADXT_Stop(h);
        ret = sfadxt_SaveAdxtHn(adxt);
    }
    sj->vtbl->destroy(sj);
    UTY_FinishTmr();
    return ret;
}

int sfadxt_DestroySub(AdxtObj *adxt) {
    ADXT_Destroy(adxt);
    return 0;
}

int sfadxt_SaveAdxtHn(AdxtObj *adxt) {
    sfadxt_save_hn = adxt;
    return 0;
}

int SFADXT_Standby(void) {
    return 0;
}

int SFADXT_Start(SfdPly *h) {
    sfadxt_WaitStart(h, 0);
    return 0;
}

int SFADXT_Stop(SfdPly *h) {
    ADXT_Stop(h->trn[3].hn.adxt->adxt);
    return 0;
}

/* matching construct: permuter, reduced by hand: the carry stored last */
int SFADXT_Pause(SfdPly *h, unsigned int mode) {
    SfdAdxCtx *ctx;
    AdxtObj *adxt;
    int size;
    int pos;
    int at;
    int carry;
    SfdRatio pair;
    ctx = h->trn[3].hn.adxt;
    adxt = ctx->adxt;
    switch (mode) {
    case 0:
        ctx->carry = 0;
        sfadxt_DoPause(h, 0);
        break;
    case 1:
        sfadxt_DoPause(h, 1);
        break;
    case 2:
        if (sfadxt_IsEndDecinfo(adxt) == 0)
            break;
        size = ADXT_GetSfreq(adxt);
        sfadxt_GetTimeOneFrmAudio(h, &pos, size);
        at = pos + ctx->carry;
        carry = at - ADXT_DiscardSmpl(adxt, at);
        pair.num = pos;
        pair.den = size;
        ctx->carry = carry;
        SFTST_GoNextFrame(&h->tim.tst, &pair);
        break;
    }
    return 0;
}

void sfadxt_WaitStart(SfdPly *h, int value) {
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    SfdTst *blk = &h->tim.tst;
    AdxtObj *adxt;
    ctx->f44 = value;
    adxt = ctx->adxt;
    if (value != 0 || h->pause != 1) {
        sfadxt_WtPause(adxt, blk, value, adxt);
    }
}

void sfadxt_DoPause(SfdPly *h, int value) {
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    SfdTst *blk = &h->tim.tst;
    AdxtObj *adxt = ctx->adxt;
    if (value != 0 || ctx->f44 != 1) {
        sfadxt_WtPause(adxt, blk, value);
    }
}

void sfadxt_WtPause(void *adxt, void *blk, int value) {
    ADXT_Pause(adxt, value);
    SFTST_Pause(blk, value);
}

void sfadxt_GetTimeOneFrmAudio(void *blk, int *result, int target) {
    int x;
    int y;
    SFTIM_GetTimeOneFrmVideo(blk, &x, &y);
    *result = UTY_MulDiv(target, x, y);
}

void SFADXT_GetWrite(SfdPly *h) {
    sfd_ReportError(h, 0xFF000C03);
}

void SFADXT_AddWrite(SfdPly *h) {
    sfd_ReportError(h, 0xFF000C03);
}

void SFADXT_GetRead(SfdPly *h) {
    sfd_ReportError(h, 0xFF000C03);
}

void SFADXT_AddRead(SfdPly *h) {
    sfd_ReportError(h, 0xFF000C03);
}

int SFADXT_Seek(SfdPly *h) {
    SfdRecAudio *info;
    SfdAdxCtx *ctx;
    AdxtObj *adxt;
    info = sfadxt_GetHd(h);
    if (info == 0)
        return 0;
    ctx = h->trn[3].hn.adxt;
    adxt = ctx->adxt;
    if (ctx->started != 0)
        return 0;
    if (info->valid == 0)
        return 0;
    ADXT_InsertHdrSfa(adxt, info->nch, info->sfreq, info->nsmpl);
    ADXT_SetTimeOfst(adxt, 0);
    ctx->started = 1;
    ctx->step = sfadxt_ExcludeSilence;
    return 0;
}

SfdRecAudio *sfadxt_GetHd(SfdPly *h) {
    SfdRec *work = h->see.rec;
    SfdAdxCtx *ctx = h->trn[3].hn.adxt;
    if (work == 0) {
        return 0;
    }
    if (ctx->f64 > 0) {
        return 0;
    }
    return &work->audio;
}
