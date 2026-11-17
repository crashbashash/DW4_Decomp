/* CRI ADXSJD: decodes an ADX stream from an input SJ into one output SJ per channel through an ADXB handle. */
#include "dw4/cri/adxb.h"
#include "dw4/cri/sj.h"
#include "dw4/cri/adxsjd.h"
#include <string.h>
#include "dw4/cri/adxcrs.h"
#include "dw4/cri/adxerrs.h"
#include "dw4/cri/adxdcd.h"

#define ADXSJD_MAX_HDR 0xc800
#define SWAP16(x) ((unsigned short)(((x) << 8) | ((x) >> 8)))

int sfa_init_cnt = 0;
int adxsjd_use_reserved = 0; /* no function reads it */
void (*adxsjd_header_hook)(AdxbObj *adxb, int rate) = 0;
AdxSjdObj adxsjd_objs[ADXSJD_MAX_OBJ] = {0};

void adxsjd_decode_prep(AdxSjdObj *sjd);
short *adxsjd_get_wr(void *obj, int *offset, int *room, int *until_trap);
void adxsjd_decexec_start(AdxSjdObj *sjd);
void adxsjd_decexec_end(AdxSjdObj *sjd);

void SFA_Init(void)
{
    sfa_init_cnt += 1;
}

void SFA_Finish(void)
{
    sfa_init_cnt -= 1;
}

void ADXSJD_Init(void)
{
    ADXB_Init();
    memset(adxsjd_objs, 0, sizeof(adxsjd_objs));
}

void ADXSJD_Finish(void)
{
    memset(adxsjd_objs, 0, sizeof(adxsjd_objs));
}

void adxsjd_clear(AdxSjdObj *sjd)
{
    sjd->trap_nsmpl = -1;
    sjd->max_dec_nsmpl = 0x7FFFFFFF;
    sjd->skip = 0;
    sjd->hdr_len = 0;
    sjd->dec_nsmpl = 0;
    sjd->dec_dtlen = 0;
    sjd->dec_pos = 0;
    sjd->trap_cnt = 0;
    sjd->trap_dtlen = 0;
    /* matching construct: permuter — the do/while(0) keeps ee-gcc from scheduling the fill store above this byte store */
    do {
        sjd->end_on_empty = 0;
    } while (0);
    sjd->fill = 0;
}

AdxSjdObj *ADXSJD_Create(SfdSj *sji, int nch, SfdSj **sjo)
{
    AdxSjdObj *sjd;
    SfdSj *sj0;
    void *buf;
    int bsize;
    int xsize;
    int i;
    int ch;

    sj0 = sjo[0];
    for (i = 0; i < ADXSJD_MAX_OBJ; i++) {
        if (adxsjd_objs[i].used == 0) {
            break;
        }
    }
    if (i == ADXSJD_MAX_OBJ) {
        return 0;
    }
    sjd = &adxsjd_objs[i];
    buf = SJRBF_GetBufPtr(sj0);
    bsize = SJRBF_GetBufSize(sj0) / 2;
    xsize = SJRBF_GetXtrSize(sj0) / 2;
    sjd->adxb = ADXB_Create(nch, buf, bsize, bsize + xsize);
    if (sjd->adxb == 0) {
        return 0;
    }
    ADXB_EntryGetWrFunc(sjd->adxb, adxsjd_get_wr, sjd);
    sjd->sji = sji;
    sjd->nch = nch;
    for (ch = 0; ch < nch; ch++) {
        sjd->sjo[ch] = sjo[ch];
    }
    sjd->stat = ADXSJD_STAT_STOP;
    adxsjd_clear(sjd);
    sjd->trap_func = 0;
    sjd->trap_obj = 0;
    sjd->flt_func = 0;
    sjd->flt_obj = 0;
    sjd->used = 1;
    return sjd;
}

void ADXSJD_Destroy(AdxSjdObj *sjd)
{
    AdxbObj *adxb;

    if (sjd != 0) {
        adxb = sjd->adxb;
        if (adxb != 0) {
            sjd->adxb = 0;
            ADXB_Destroy(adxb);
        }
        ADXCRS_Lock();
        memset(sjd, 0, sizeof(AdxSjdObj));
        ADXCRS_Unlock();
    }
}

char ADXSJD_GetStat(AdxSjdObj *sjd)
{
    return sjd->stat;
}

void ADXSJD_SetInSj(AdxSjdObj *sjd, SfdSj *sji)
{
    sjd->sji = sji;
    ADXB_SetAhxInSj(sjd->adxb, sji);
    ADXB_SetAc3InSj(sjd->adxb, sji);
}

void ADXSJD_SetOutSj(AdxSjdObj *sjd, int ch, SfdSj *sjo)
{
    sjd->sjo[ch] = sjo;
}

void ADXSJD_SetMaxDecSmpl(AdxSjdObj *sjd, int value)
{
    sjd->max_dec_nsmpl = value;
    ADXB_SetAhxDecSmpl(sjd->adxb, value);
    ADXB_SetAc3DecSmpl(sjd->adxb, value);
}

void ADXSJD_TermSupply(AdxSjdObj *sjd)
{
    ADXB_AhxTermSupply(sjd->adxb);
    ADXB_Ac3TermSupply(sjd->adxb);
}

void ADXSJD_Start(AdxSjdObj *sjd)
{
    adxsjd_clear(sjd);
    sjd->stat = ADXSJD_STAT_DECHDR;
}

void ADXSJD_Stop(AdxSjdObj *sjd)
{
    ADXB_Stop(sjd->adxb);
    sjd->stat = ADXSJD_STAT_STOP;
}

void adxsjd_decode_prep(AdxSjdObj *sjd)
{
    SfdSj *sji;
    AdxbObj *adxb;
    SfdSjChunk ck;
    SfdSjChunk part;
    int i;
    int hdrlen;
    int type;

    sji = sjd->sji;
    adxb = sjd->adxb;
    sji->vtbl->getChunk(sji, 1, ADXSJD_MAX_HDR, &ck);
    for (i = 0; i < ck.len; i++) {
        if (ck.data[i] != 0) {
            break;
        }
    }
    SJ_SplitChunk(&ck, i, &part, &ck);
    sji->vtbl->putChunk(sji, 0, &part);
    if (ck.len < 16) {
        sji->vtbl->ungetChunk(sji, 1, &ck);
        return;
    }
    hdrlen = ADXB_DecodeHeader(adxb, ck.data, ck.len);
    if (hdrlen == 0 || ck.len < hdrlen) {
        sji->vtbl->ungetChunk(sji, 1, &ck);
        return;
    }
    if (hdrlen < 0) {
        if ((short)adxb->def_format != 0) {
            ADXB_SetDefPrm(adxb);
            hdrlen = 0;
        } else {
            sji->vtbl->ungetChunk(sji, 1, &ck);
            ADXERR_CallErrFunc2("E03010901 ADXB_DecodeHeader: ", "Can not decode this file format.");
            sjd->stat = ADXSJD_STAT_ERROR;
            return;
        }
    }
    sjd->hdr_len = hdrlen;
    if (ADXB_GetFormat(adxb) == 4) {
        sjd->end_on_empty = 1;
    }
    if (ADXB_GetFormat(adxb) == 2) {
        memcpy(sjd->hdr, ck.data, ck.len > 64 ? 64 : ck.len);
    }
    type = ADXB_GetFormat(adxb);
    if (type == 10 || type == 11 || type == 12 || type == 20 || type == 15) {
        sji->vtbl->ungetChunk(sji, 1, &ck);
    } else {
        SJ_SplitChunk(&ck, hdrlen, &ck, &part);
        sji->vtbl->putChunk(sji, 0, &ck);
        sji->vtbl->ungetChunk(sji, 1, &part);
    }
    if (adxb->pl2 != 0 && adxsjd_header_hook != 0) {
        adxsjd_header_hook(adxb, adxb->sfreq);
    }
    sjd->stat = ADXSJD_STAT_DECODE;
}

short *adxsjd_get_wr(void *obj, int *offset, int *room, int *until_trap)
{
    AdxSjdObj *sjd = obj;
    SfdSj *sjo = sjd->sjo[0];
    int ch;
    int n;

    for (ch = 0; ch < ADXB_GetNumChan(sjd->adxb); ch++) {
        sjd->sjo[ch]->vtbl->getChunk(sjd->sjo[ch], 0, 0x4000, &sjd->ck[ch]);
    }
    *offset = (sjd->ck[0].data - (char *)SJRBF_GetBufPtr(sjo)) / 2;
    n = sjd->ck[0].len / 2;
    *room = n < sjd->max_dec_nsmpl ? n : sjd->max_dec_nsmpl;
    if (sjd->trap_nsmpl >= 0) {
        *until_trap = sjd->trap_nsmpl - sjd->trap_cnt;
    } else {
        *until_trap = 0x1fffffff;
    }
    return ADXB_GetPcmBuf(sjd->adxb);
}

void adxsjd_decexec_start(AdxSjdObj *sjd)
{
    AdxbObj *adxb;
    SfdSj *sji;
    SfdSjChunk rest;
    short ofst;
    int i;
    int len;
    int found;

    adxb = sjd->adxb;
    sji = sjd->sji;
    if (sjd->trap_nsmpl >= 0 && sjd->trap_cnt >= sjd->trap_nsmpl && sjd->trap_func != 0) {
        sjd->trap_func(sjd->trap_obj);
    }
    if (sjd->end_on_empty == 1 && sji->vtbl->getNumData(sji, 1) == 0) {
        sjd->stat = ADXSJD_STAT_DECEND;
        return;
    }
    sji->vtbl->getChunk(sji, 1, 0x7fffffff, &sjd->cki);
    if (ADXB_GetFormat(adxb) == 0 && sjd->cki.len >= 4
        && (unsigned short)((*(unsigned short *)sjd->cki.data << 8) | ((unsigned char *)sjd->cki.data)[1]) == 0x8001) {
        sjd->stat = ADXSJD_STAT_DECEND;
        if (ADX_DecodeFooter(sjd->cki.data, sjd->cki.len, &ofst) == 0) {
            if (sjd->cki.len < ofst) {
                sji->vtbl->ungetChunk(sji, 1, &sjd->cki);
                return;
            }
            SJ_SplitChunk(&sjd->cki, ofst, &sjd->cki, &rest);
            sji->vtbl->putChunk(sji, 0, &sjd->cki);
            sji->vtbl->ungetChunk(sji, 1, &rest);
        }
        if (sjd->lnksw != 0) {
            for (;;) {
                sji->vtbl->getChunk(sji, 1, 0x7fffffff, &sjd->cki);
                len = sjd->cki.len;
                if (len == 0) {
                    break;
                }
                for (i = 0; i < sjd->cki.len; i++) {
                    if (sjd->cki.data[i] != 0) {
                        break;
                    }
                }
                found = i < len;
                SJ_SplitChunk(&sjd->cki, i, &sjd->cki, &rest);
                sji->vtbl->putChunk(sji, 0, &sjd->cki);
                sji->vtbl->ungetChunk(sji, 1, &rest);
                if (found) {
                    break;
                }
            }
        }
        return;
    }
    if (sjd->dec_pos >= ADXSJD_GetTotalNumSmpl(sjd)) {
        sjd->stat = ADXSJD_STAT_DECEND;
        sji->vtbl->ungetChunk(sji, 1, &sjd->cki);
        return;
    }
    if (ADXSJD_GetBlkSmpl(sjd) > sjd->sjo[0]->vtbl->getNumData(sjd->sjo[0], 0) / 2) {
        sji->vtbl->ungetChunk(sji, 1, &sjd->cki);
        return;
    }
    if (ADXB_GetFormat(adxb) == 10) {
        sji->vtbl->ungetChunk(sji, 1, &sjd->cki);
    }
    if (ADXB_GetFormat(adxb) == 15) {
        sji->vtbl->ungetChunk(sji, 1, &sjd->cki);
    }
    ADXB_EntryData(adxb, sjd->cki.data, sjd->cki.len);
    ADXB_Start(adxb);
}

void adxsjd_decexec_end(AdxSjdObj *sjd)
{
    AdxbObj *adxb;
    SfdSj *sji;
    SfdSjChunk ck;
    SfdSjChunk rest;
    int total;
    int bytes;
    int n;
    int ch;

    adxb = sjd->adxb;
    sji = sjd->sji;
    total = ADXB_GetTotalNumSmpl(adxb);
    bytes = ADXB_GetDecDtLen(adxb);
    n = ADXB_GetDecNumSmpl(adxb);
    total -= sjd->dec_pos;
    if (n >= total) {
        n = total;
    }
    SJ_SplitChunk(&sjd->cki, bytes, &ck, &rest);
    sji->vtbl->putChunk(sji, 0, &ck);
    sji->vtbl->ungetChunk(sji, 1, &rest);
    for (ch = 0; ch < ADXB_GetNumChan(sjd->adxb); ch++) {
        SJ_SplitChunk(&sjd->ck[ch], n * 2, &ck, &rest);
        if (sjd->flt_func != 0) {
            sjd->flt_func(sjd->flt_obj, ch, ck.data, ck.len);
        }
        sjd->sjo[ch]->vtbl->putChunk(sjd->sjo[ch], 1, &ck);
        sjd->sjo[ch]->vtbl->ungetChunk(sjd->sjo[ch], 0, &rest);
    }
    sjd->dec_nsmpl += n;
    sjd->dec_dtlen += bytes;
    sjd->dec_pos += n;
    sjd->trap_cnt += n;
    sjd->trap_dtlen += bytes;
    ADXB_Reset(adxb);
}

void adxsjd_decexec_extra(AdxSjdObj *sjd)
{
    AdxbObj *adxb = sjd->adxb;
    int total = ADXB_GetTotalNumSmpl(adxb);
    int added = ADXB_GetDecDtLen(adxb);
    int step = ADXB_GetDecNumSmpl(adxb);
    int remaining = total - sjd->dec_pos;

    if (step < remaining) {
        remaining = step;
    }
    /* matching construct: permuter — the three updates moved from f52, f44, f48 order to this one */
    sjd->dec_nsmpl += remaining;
    sjd->dec_dtlen += added;
    sjd->dec_pos += remaining;
}

void adxsjd_decode_exec(AdxSjdObj *sjd)
{
    AdxbObj *adxb;
    short type;

    adxb = sjd->adxb;
    if (ADXB_GetStat(adxb) == 0) {
        adxsjd_decexec_start(sjd);
    }
    ADXB_ExecHndl(adxb);
    if (ADXB_GetStat(adxb) == 3) {
        adxsjd_decexec_end(sjd);
    }
    type = adxb->format;
    if (type == 10 || type == 20 || type == 11 || type == 12 || type == 15) {
        adxsjd_decexec_extra(sjd);
    }
}

void adxsjd_insert_proc(AdxSjdObj *sjd);
void adxsjd_discard_proc(AdxSjdObj *sjd);

void ADXSJD_ExecHndl(AdxSjdObj *sjd)
{
    if (sjd->fill > 0) {
        ADXCRS_Lock();
        adxsjd_insert_proc(sjd);
        ADXCRS_Unlock();
    }
    if (sjd->stat == ADXSJD_STAT_DECODE) {
        adxsjd_decode_exec(sjd);
    } else if (sjd->stat == ADXSJD_STAT_DECHDR) {
        adxsjd_decode_prep(sjd);
    }
    if (sjd->skip > 0) {
        ADXCRS_Lock();
        adxsjd_discard_proc(sjd);
        ADXCRS_Unlock();
    }
}

void adxsjd_insert_proc(AdxSjdObj *sjd)
{
    SfdSjChunk ck;
    int i;
    int n;
    int half;

    n = sjd->fill * 2;
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 0, 0x7fffffff, &ck);
        if (ck.len <= n) {
            n = ck.len;
        }
        sjd->sjo[i]->vtbl->ungetChunk(sjd->sjo[i], 0, &ck);
    }
    half = n / 2;
    n = half * 2;
    if (n <= 0) {
        return;
    }
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 0, n, &ck);
        memset(ck.data, 0, n);
        sjd->sjo[i]->vtbl->putChunk(sjd->sjo[i], 1, &ck);
    }
    sjd->fill -= half;
}

void adxsjd_discard_proc(AdxSjdObj *sjd)
{
    SfdSjChunk ck;
    int i;
    int n;
    int half;

    n = sjd->skip * 2;
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 1, 0x7fffffff, &ck);
        if (ck.len <= n) {
            n = ck.len;
        }
        sjd->sjo[i]->vtbl->ungetChunk(sjd->sjo[i], 1, &ck);
    }
    half = n / 2;
    n = half * 2;
    if (n <= 0) {
        return;
    }
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 1, n, &ck);
        sjd->sjo[i]->vtbl->putChunk(sjd->sjo[i], 0, &ck);
    }
    sjd->skip -= half;
}

void ADXSJD_ExecServer(void)
{
    AdxSjdObj *sjd = adxsjd_objs;
    int i;

    for (i = ADXSJD_MAX_OBJ - 1; i >= 0; i--, sjd++) {
        if (sjd->used == 1) {
            ADXSJD_ExecHndl(sjd);
        }
    }
}

int ADXSJD_GetDecDtLen(AdxSjdObj *sjd)
{
    return sjd->dec_dtlen;
}

int ADXSJD_GetDecNumSmpl(AdxSjdObj *sjd)
{
    return sjd->dec_nsmpl;
}

void ADXSJD_EntryDecFunc(AdxSjdObj *sjd, void (*func)(void *context, int count, int bytes), void *context)
{
    ADXB_EntryDecFunc(sjd->adxb, func, context);
}

void ADXSJD_SetDecPos(AdxSjdObj *sjd, int value)
{
    sjd->dec_pos = value;
}

int ADXSJD_GetDecPos(AdxSjdObj *sjd)
{
    return sjd->dec_pos;
}

void ADXSJD_SetLnkSw(AdxSjdObj *sjd, int value)
{
    sjd->lnksw = value;
}

int ADXSJD_GetLnkSw(AdxSjdObj *sjd)
{
    return sjd->lnksw;
}

void ADXSJD_SetExtString(AdxSjdObj *sjd, const char *text)
{
    ADXB_SetExtString(sjd->adxb, text);
}

void ADXSJD_SetDefExtString(const char *text)
{
    ADXB_SetDefExtString(text);
}

void ADXSJD_ResetDefFmt(AdxSjdObj *sjd)
{
    ADXB_ResetDefFmt(sjd->adxb);
}

int ADXSJD_AdjustSmpl(AdxSjdObj *sjd, int amount)
{
    ADXCRS_Lock();
    if (amount > 0) {
        sjd->fill += amount;
    } else {
        sjd->skip -= amount;
    }
    ADXCRS_Unlock();
    return amount;
}

void ADXSJD_EntryFltFunc(AdxSjdObj *sjd, void (*func)(void *context, int ch, char *data, int len), void *context)
{
    sjd->flt_func = func;
    sjd->flt_obj = context;
}

void ADXSJD_EntryTrapFunc(AdxSjdObj *sjd, void (*func)(void *context), void *context)
{
    sjd->trap_func = func;
    sjd->trap_obj = context;
}

void ADXSJD_SetTrapNumSmpl(AdxSjdObj *sjd, int value)
{
    sjd->trap_nsmpl = value;
}

int ADXSJD_GetTrapNumSmpl(AdxSjdObj *sjd)
{
    return sjd->trap_nsmpl;
}

void ADXSJD_SetTrapCnt(AdxSjdObj *sjd, int value)
{
    sjd->trap_cnt = value;
}

int ADXSJD_GetTrapCnt(AdxSjdObj *sjd)
{
    return sjd->trap_cnt;
}

void ADXSJD_SetTrapDtLen(AdxSjdObj *sjd, int value)
{
    sjd->trap_dtlen = value;
}

int ADXSJD_GetTrapDtLen(AdxSjdObj *sjd)
{
    return sjd->trap_dtlen;
}

int ADXSJD_GetFormat(AdxSjdObj *sjd)
{
    return ADXB_GetFormat(sjd->adxb);
}

int ADXSJD_GetSfreq(AdxSjdObj *sjd)
{
    return ADXB_GetSfreq(sjd->adxb);
}

int ADXSJD_GetNumChan(AdxSjdObj *sjd)
{
    return ADXB_GetNumChan(sjd->adxb);
}

int ADXSJD_GetOutBps(AdxSjdObj *sjd)
{
    return ADXB_GetOutBps(sjd->adxb);
}

int ADXSJD_GetBlkSmpl(AdxSjdObj *sjd)
{
    return ADXB_GetBlkSmpl(sjd->adxb);
}

int ADXSJD_GetBlkLen(AdxSjdObj *sjd)
{
    return ADXB_GetBlkLen(sjd->adxb);
}

int ADXSJD_GetTotalNumSmpl(AdxSjdObj *sjd)
{
    return ADXB_GetTotalNumSmpl(sjd->adxb);
}

int ADXSJD_GetCof(AdxSjdObj *sjd)
{
    return ADXB_GetCof(sjd->adxb);
}

int ADXSJD_GetNumLoop(AdxSjdObj *sjd)
{
    return ADXB_GetNumLoop(sjd->adxb);
}

int ADXSJD_GetLpInsNsmpl(AdxSjdObj *sjd)
{
    return ADXB_GetLpInsNsmpl(sjd->adxb);
}

int ADXSJD_GetLpStartPos(AdxSjdObj *sjd)
{
    return ADXB_GetLpStartPos(sjd->adxb);
}

int ADXSJD_GetLpStartOfst(AdxSjdObj *sjd)
{
    if (sjd == 0) {
        return 0;
    }
    return ADXB_GetLpStartOfst(sjd->adxb);
}

int ADXSJD_GetLpEndPos(AdxSjdObj *sjd)
{
    return ADXB_GetLpEndPos(sjd->adxb);
}

int ADXSJD_GetLpEndOfst(AdxSjdObj *sjd)
{
    return ADXB_GetLpEndOfst(sjd->adxb);
}

int ADXSJD_GetAinfLen(AdxSjdObj *sjd)
{
    return ADXB_GetAinfLen(sjd->adxb);
}

short ADXSJD_GetDefOutVol(AdxSjdObj *sjd)
{
    if (ADXB_GetAinfLen(sjd->adxb) > 0 && (sjd->stat == ADXSJD_STAT_DECODE || sjd->stat == ADXSJD_STAT_DECEND)) {
        return ADXB_GetDefOutVol(sjd->adxb);
    }
    return 0;
}

short ADXSJD_GetDefPan(AdxSjdObj *sjd, int arg)
{
    if (ADXB_GetAinfLen(sjd->adxb) > 0) {
        if (sjd->stat == ADXSJD_STAT_DECODE || sjd->stat == ADXSJD_STAT_DECEND) {
            return ADXB_GetDefPan(sjd->adxb, arg);
        }
    }
    return -128;
}

char *ADXSJD_GetDataId(AdxSjdObj *sjd)
{
    if (ADXB_GetAinfLen(sjd->adxb) > 0 && (sjd->stat == ADXSJD_STAT_DECODE || sjd->stat == ADXSJD_STAT_DECEND)) {
        return ADXB_GetDataId(sjd->adxb);
    }
    return 0;
}

int ADXSJD_GetHdrLen(AdxSjdObj *sjd)
{
    return sjd->hdr_len;
}

int ADXSJD_GetFmtBps(AdxSjdObj *sjd)
{
    return ADXB_GetFmtBps(sjd->adxb);
}

char *ADXSJD_GetSpsdInfo(AdxSjdObj *sjd)
{
    return sjd->hdr;
}

void ADXSJD_TakeSnapshot(AdxSjdObj *sjd)
{
    ADXB_TakeSnapshot(sjd->adxb);
}

void ADXSJD_RestoreSnapshot(AdxSjdObj *sjd)
{
    ADXB_RestoreSnapshot(sjd->adxb);
}
