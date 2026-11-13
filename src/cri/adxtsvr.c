/* CRI ADXT server: the per-handle state machine, the loop and link traps, and the error checks. */
#include "dw4/cri/adxt.h"

#define ADXT_MIN_OBUF_NDATA 64      /* output bytes below which a channel counts as drained */

enum { ADXB_FORMAT_SPSD = 2 };
enum { LSC_STAT_ERROR = 3 };

typedef void (*AdxtDecInfoFunc)(AdxtObj *adxt, int sfreq, int nch, int total_nsmpl);

extern AdxtDecInfoFunc adxt_decinfo_func;
extern int adxt_playing_nch;
extern int adxt_playing_ndata;
extern int adxt_eos_rna_ndata;
/* The V-sync count; the vertical-blank interrupt path increments it. */
extern volatile int adxt_vsync_cnt;

extern char E8101201_adxt_trap_entry_not_enough_data[];
extern char E9081001_adxt_stat_decinfo_can_t_play_this_number_of_channels[];
extern char E02080842_ADXT_ExecHndl_parameter_error[];

int ADX_DecodeFooter(char *buf, int len, short *ftrlen);
int ADX_ScanInfoCode(char *buf, int len, short *pos);
void ADXSJD_ExecHndl(AdxSjdObj *sjd);
int ADXSJD_GetFormat(AdxSjdObj *sjd);
int ADXSJD_GetNumLoop(AdxSjdObj *sjd);
int ADXSJD_GetLpEndOfst(AdxSjdObj *sjd);
char *ADXSJD_GetSpsdInfo(AdxSjdObj *sjd);
void ADXSJD_SaveDly(AdxSjdObj *sjd);
void ADXSJD_RestoreDly(AdxSjdObj *sjd);
int ADXSTM_GetStatRead(AdxStmObj *stm);
void ADXSTM_Stop(AdxStmObj *stm);
int ADXRNA_GetNumRoom(AdxRna *rna);
void ADXRNA_SetNumChan(AdxRna *rna, int nch);
void ADXRNA_SetSfreq(AdxRna *rna, int sfreq);
void ADXRNA_SetBitPerSmpl(AdxRna *rna, int bps);
void ADXRNA_SetTotalNumSmpl(AdxRna *rna, int nsmpl);
void ADXRNA_SetStmHdInfo(AdxRna *rna, char *info);
void ADXAMP_SetSfreq(AdxAmpObj *amp, int sfreq);
int LSC_GetStat(LscObj *lsc);

void adxt_trap_entry(AdxtObj *adxt);

/* Trap at the loop start: keeps the decoder's history there and arms the loop-end trap. */
void adxt_trap_entry_lp(AdxtObj *adxt)
{
    AdxSjdObj *sjd = adxt->sjd;
    int lpspos = ADXSJD_GetLpStartPos(sjd);
    int lpsofst = ADXSJD_GetLpStartOfst(sjd);
    int lpepos = ADXSJD_GetLpEndPos(sjd);

    ADXSJD_SaveDly(sjd);
    ADXSJD_SetTrapCnt(sjd, 0);
    adxt->trpnsmpl = lpepos - lpspos;
    ADXSJD_SetTrapNumSmpl(sjd, adxt->trpnsmpl);
    ADXSJD_SetTrapDtLen(sjd, lpsofst);
    ADXSJD_SetDecPos(sjd, lpspos);
    ADXSJD_EntryTrapFunc(sjd, adxt_trap_entry, adxt);
}

/* Trap at the loop end: skips the input to the next loop start and restores the decoder's history. */
void adxt_trap_entry(AdxtObj *adxt)
{
    AdxSjdObj *sjd = adxt->sjd;
    SfdSj *sji = adxt->sji;
    int lpspos;
    int lpsofst;
    int lpepos;
    SfdSjChunk ck;

    lpspos = ADXSJD_GetLpStartPos(sjd);
    lpsofst = ADXSJD_GetLpStartOfst(sjd);
    lpepos = ADXSJD_GetLpEndPos(sjd);
    if ((adxt->pmode == ADXT_PMODE_MEM || adxt->pmode == ADXT_PMODE_SJ) && adxt->lpflg == 0) {
        ADXSJD_SetTrapNumSmpl(adxt->sjd, -1);
        return;
    }
    sji->vtbl->getChunk(sji, SJ_LIN_DATA, adxt->lp_skiplen, &ck);
    if (ck.len < adxt->lp_skiplen) {
        ADXERR_CallErrFunc1(E8101201_adxt_trap_entry_not_enough_data);
    }
    sji->vtbl->putChunk(sji, SJ_LIN_FREE, &ck);
    ADXSJD_SetTrapCnt(sjd, 0);
    adxt->trpnsmpl = lpepos - lpspos;
    ADXSJD_SetTrapNumSmpl(sjd, adxt->trpnsmpl);
    ADXSJD_SetTrapDtLen(sjd, lpsofst);
    ADXSJD_SetDecPos(sjd, lpspos);
    if (adxt->pmode == ADXT_PMODE_MEM) {
        sji->vtbl->reset(sji);
        sji->vtbl->getChunk(sji, SJ_LIN_DATA, lpsofst, &ck);
        sji->vtbl->putChunk(sji, SJ_LIN_FREE, &ck);
    }
    ADXSJD_RestoreDly(sjd);
    adxt->lpcnt++;
}

/* The stream reached the loop end sector: rewind it to the loop start, or let it run on when looping is off. */
void adxt_eos_entry(AdxtObj *adxt)
{
    AdxStmObj *stm = adxt->stm;
    AdxSjdObj *sjd = adxt->sjd;
    int lpsofst;

    if (stm == 0 || sjd == 0) {
        return;
    }
    lpsofst = ADXSJD_GetLpStartOfst(sjd);
    if (adxt->lpflg == 0) {
        ADXSJD_SetTrapNumSmpl(adxt->sjd, -1);
        ADXSTM_SetEos(adxt->stm, 0x7fffffff);
    } else {
        ADXSTM_Seek(stm, lpsofst / ADXT_SCT_LEN);
    }
}

void adxt_set_outpan(AdxtObj *adxt)
{
    if (ADXSJD_GetNumChan(adxt->sjd) == 1) {
        ADXT_SetOutPan(adxt, 0, adxt->outpan[0]);
        return;
    }
    ADXT_SetOutPan(adxt, 0, adxt->outpan[0]);
    ADXT_SetOutPan(adxt, 1, adxt->outpan[1]);
}

/* Trap at the end of a linked stream: drops the footer and the next stream's header from the input
 * (they may straddle two chunks) and restarts the decoder on the next stream. */
void adxt_trap_entry_lnk(AdxtObj *adxt)
{
    AdxSjdObj *sjd;
    SfdSj *sj;
    SfdSjChunk ck0;
    SfdSjChunk rest0;
    SfdSjChunk ck1;
    SfdSjChunk rest1;
    short skip0;
    short skip1;
    int len;
    int found0;
    int found1;
    int len1;

    sjd = adxt->sjd;
    sj = adxt->sji;
    if (adxt->lnkflg == 0) {
        return;
    }
    skip1 = 0;
    sj->vtbl->getChunk(sj, SJ_LIN_DATA, 0x7fffffff, &ck0);
    sj->vtbl->getChunk(sj, SJ_LIN_DATA, 0x7fffffff, &ck1);
    if (ADX_DecodeFooter(ck0.data, ck0.len, &skip0) != 0) {
        ADXT_SetLnkSw(adxt, 0);
        sj->vtbl->ungetChunk(sj, SJ_LIN_DATA, &ck1);
        sj->vtbl->ungetChunk(sj, SJ_LIN_DATA, &ck0);
        return;
    }
    len = skip0;
    found0 = ADX_ScanInfoCode(ck0.data + len, ck0.len - len, &skip0);
    found1 = -1;
    if (found0 != 0) {
        found1 = ADX_ScanInfoCode(ck1.data, ck1.len, &skip1);
    }
    len += skip0;
    len1 = skip1;
    if (found0 != 0 && found1 != 0) {
        sj->vtbl->ungetChunk(sj, SJ_LIN_DATA, &ck1);
        sj->vtbl->ungetChunk(sj, SJ_LIN_DATA, &ck0);
        ADXT_SetLnkSw(adxt, 0);
        return;
    } else if (found0 == 0) {
        sj->vtbl->ungetChunk(sj, SJ_LIN_DATA, &ck1);
        SJ_SplitChunk(&ck0, len, &ck0, &rest0);
        sj->vtbl->putChunk(sj, SJ_LIN_FREE, &ck0);
        sj->vtbl->ungetChunk(sj, SJ_LIN_DATA, &rest0);
    } else {
        sj->vtbl->putChunk(sj, SJ_LIN_FREE, &ck0);
        SJ_SplitChunk(&ck1, len1, &ck1, &rest1);
        sj->vtbl->putChunk(sj, SJ_LIN_FREE, &ck1);
        sj->vtbl->ungetChunk(sj, SJ_LIN_DATA, &rest1);
    }
    adxt->decofst += ADXSJD_GetDecNumSmpl(sjd);
    ADXSJD_Stop(sjd);
    ADXSJD_Start(sjd);
    ADXSJD_ExecHndl(sjd);
    if (ADXSJD_GetStat(sjd) != ADXSJD_STAT_DECODE) {
        ADXT_SetLnkSw(adxt, 0);
    } else {
        ADXSJD_SetMaxDecSmpl(sjd, adxt->maxdecsmpl);
        ADXSJD_SetTrapNumSmpl(sjd, ADXSJD_GetTotalNumSmpl(sjd));
        ADXSJD_SetTrapDtLen(sjd, 0);
        ADXSJD_SetTrapCnt(sjd, 0);
    }
}

/* State DECINFO: starts a pending file stream, waits for the header, then sizes the decode step,
 * sets the loop traps and configures the renderer for the stream. */
void adxt_stat_decinfo(AdxtObj *adxt)
{
    char nchstr[32];
    AdxSjdObj *sjd;
    int sctlen;
    int fxch;
    int fxlev;
    int sfreq;
    int nch;
    int total_nsmpl;
    int nloop;
    int lpeofst;
    int blkbytes;

    sctlen = ADXT_SCT_LEN;
    fxch = 0;
    sjd = adxt->sjd;
    fxlev = 0;
    adxt->pad_nsmpl = 0;
    if ((adxt->pmode == ADXT_PMODE_FNAME || adxt->pmode == ADXT_PMODE_AFS) && adxt->stm_req == 1) {
        if (ADXSTM_GetStat(adxt->stm) == ADXSTM_STAT_READING) {
            return;
        }
        if (adxt->sjf != 0) {
            adxt->sjf->vtbl->reset(adxt->sjf);
        }
        adxt_start_stm(adxt, adxt->fname, adxt->dir, adxt->ofst, adxt->nsct);
        adxt->stm_req = 0;
    }
    if (ADXSJD_GetStat(sjd) != ADXSJD_STAT_DECODE) {
        return;
    }
    nch = ADXSJD_GetNumChan(sjd);
    if (adxt->maxnch < nch) {
        ADXERR_ItoA2(nch, adxt->maxnch, nchstr, 16);
        ADXERR_CallErrFunc2(E9081001_adxt_stat_decinfo_can_t_play_this_number_of_channels, nchstr);
        ADXT_Stop(adxt);
        return;
    }
    sfreq = ADXSJD_GetSfreq(sjd);
    nloop = ADXSJD_GetNumLoop(sjd);
    if (nloop > 0) {
        adxt->maxdecsmpl = (sfreq / adxt->svrfreq) * 3;
    } else {
        adxt->maxdecsmpl = (sfreq / adxt->svrfreq) * 3 / 2;
    }
    blkbytes = ADXSJD_GetBlkSmpl(sjd) * 2;
    adxt->maxdecsmpl = ((adxt->maxdecsmpl + blkbytes) / blkbytes) * blkbytes;
    ADXSJD_SetMaxDecSmpl(sjd, adxt->maxdecsmpl);
    if (nloop > 0) {
        if (adxt->pmode == ADXT_PMODE_MEM) {
            adxt->lp_skiplen = 0;
        } else {
            lpeofst = ADXSJD_GetLpEndOfst(sjd);
            adxt->lp_skiplen = sctlen - lpeofst % sctlen;
            adxt->lp_skiplen = adxt->lp_skiplen % sctlen;
            adxt->lesct = (lpeofst + sctlen - 1) / sctlen;
            ADXSTM_SetEos(adxt->stm, adxt->lesct);
            ADXSTM_EntryEosFunc(adxt->stm, adxt_eos_entry, adxt);
        }
        ADXSJD_GetLpEndPos(sjd);
        adxt->trpnsmpl = ADXSJD_GetLpStartPos(sjd);
        ADXSJD_SetTrapNumSmpl(sjd, adxt->trpnsmpl);
        ADXSJD_SetTrapDtLen(sjd, 0);
        ADXSJD_SetTrapCnt(sjd, 0);
        ADXSJD_EntryTrapFunc(sjd, adxt_trap_entry_lp, adxt);
    } else {
        if (adxt->stm != 0) {
            ADXSTM_SetEos(adxt->stm, 0x7fffffff);
        }
        ADXSJD_SetTrapNumSmpl(sjd, ADXSJD_GetTotalNumSmpl(sjd));
        ADXSJD_SetTrapDtLen(sjd, 0);
        ADXSJD_SetTrapCnt(sjd, 0);
        ADXSJD_EntryTrapFunc(sjd, adxt_trap_entry_lnk, adxt);
    }
    sfreq = ADXSJD_GetSfreq(sjd);
    nch = ADXSJD_GetNumChan(sjd);
    total_nsmpl = ADXSJD_GetTotalNumSmpl(sjd);
    ADXRNA_SetBitPerSmpl(adxt->rna, ADXSJD_GetOutBps(sjd));
    ADXRNA_SetSfreq(adxt->rna, sfreq);
    ADXRNA_SetNumChan(adxt->rna, nch);
    ADXRNA_SetTotalNumSmpl(adxt->rna, total_nsmpl);
    ADXRNA_SetOutVol(adxt->rna, adxt->outvol + ADXSJD_GetDefOutVol(adxt->sjd));
    ADXT_GetFx(adxt, &fxch, &fxlev);
    if (fxch != 0 || fxlev != 0) {
        ADXT_SetFx(adxt, fxch, fxlev);
    }
    adxt_set_outpan(adxt);
    if (adxt->amp != 0) {
        ADXAMP_SetSfreq(adxt->amp, sfreq);
    }
    if (ADXSJD_GetFormat(sjd) == ADXB_FORMAT_SPSD) {
        ADXRNA_SetStmHdInfo(adxt->rna, ADXSJD_GetSpsdInfo(sjd));
    }
    ADXRNA_SetTransSw(adxt->rna, 1);
    if (adxt_decinfo_func != 0) {
        adxt_decinfo_func(adxt, sfreq, nch, total_nsmpl);
    }
    adxt->stat = ADXT_STAT_PREP;
}

AdxtDecInfoFunc ADXT_EntryDecInfoFunc(AdxtDecInfoFunc func)
{
    AdxtDecInfoFunc old;

    old = adxt_decinfo_func;
    adxt_decinfo_func = func;
    return old;
}

/* State PREP: once enough output is queued, or the decoder has ended, playback starts; a handle
 * told to wait for its start only reports that it is ready. A stream that has already ended gets
 * one decode step of silence in every output channel. */
void adxt_stat_prep(AdxtObj *adxt)
{
    SfdSjChunk ck;
    AdxRna *rna;
    AdxSjdObj *sjd;
    int ndata;
    int nroom;
    int nch;
    int len;
    int i;
    SfdSj *sjo;

    rna = adxt->rna;
    sjd = adxt->sjd;
    ndata = ADXRNA_GetNumData(rna);
    nroom = ADXRNA_GetNumRoom(rna);
    if (ndata >= adxt->maxdecsmpl * 2 || ADXSJD_GetBlkSmpl(sjd) >= nroom
        || ADXSJD_GetStat(adxt->sjd) == ADXSJD_STAT_DECEND) {
        if (adxt->pstwait_flag == 0) {
            if (adxt->pause_flag == 0) {
                ADXRNA_SetPlaySw(rna, 1);
                adxt->vtime = 0;
                adxt->vbase = adxt_vsync_cnt;
            }
            adxt->stat = ADXT_STAT_PLAYING;
        }
        adxt->pstready_flag = 1;
    }
    if (ADXSJD_GetStat(adxt->sjd) == ADXSJD_STAT_DECEND) {
        nch = ADXT_GetNumChan(adxt);
        len = adxt->maxdecsmpl * nch * 2;
        for (i = 0; i < nch; i++) {
            sjo = adxt->sjo[i];
            sjo->vtbl->getChunk(sjo, SJ_LIN_FREE, len, &ck);
            memset(ck.data, 0, ck.len);
            sjo->vtbl->putChunk(sjo, SJ_LIN_DATA, &ck);
        }
    }
}

/* State PLAYING: the decoder has ended once every output channel is drained. */
void adxt_stat_playing(AdxtObj *adxt)
{
    SfdSj *sjo;
    int nch;
    int i;

    if (ADXSJD_GetStat(adxt->sjd) == ADXSJD_STAT_DECEND) {
        nch = ADXSJD_GetNumChan(adxt->sjd);
        adxt_playing_nch = nch;
        for (i = 0; i < nch; i++) {
            sjo = adxt->sjo[i];
            adxt_playing_ndata = sjo->vtbl->getNumData(sjo, SJ_LIN_DATA);
            if (adxt_playing_ndata >= ADXT_MIN_OBUF_NDATA) {
                break;
            }
        }
        if (i == nch) {
            adxt->stat = ADXT_STAT_DECEND;
        }
    }
}

/* State DECEND: pads every output channel with silence up to one decode step, and stops the
 * renderer (state PLAYEND) once all queued samples have been played. */
void adxt_stat_decend(AdxtObj *adxt)
{
    SfdSjChunk ck[2];
    SfdSjChunk rest[2];
    int nch;
    int i;
    unsigned int nsmpl;
    unsigned int n;
    int nmax;
    int m;

    adxt_eos_rna_ndata = ADXRNA_GetNumData(adxt->rna);
    nch = ADXSJD_GetNumChan(adxt->sjd);
    ADXCRS_Lock();
    nsmpl = adxt->maxdecsmpl;
    for (i = 0; i < nch; i++) {
        adxt->sjo[i]->vtbl->getChunk(adxt->sjo[i], SJ_LIN_FREE, nsmpl * 2, &ck[i]);
        n = (unsigned int)ck[i].len >> 1;
        if (n < nsmpl) {
            nsmpl = n;
        }
    }
    for (i = 0; i < nch; i++) {
        SJ_SplitChunk(&ck[i], nsmpl * 2, &ck[i], &rest[i]);
        memset(ck[i].data, 0, ck[i].len);
        adxt->sjo[i]->vtbl->putChunk(adxt->sjo[i], SJ_LIN_DATA, &ck[i]);
        adxt->sjo[i]->vtbl->ungetChunk(adxt->sjo[i], SJ_LIN_FREE, &rest[i]);
    }
    nmax = 0;
    adxt->pad_nsmpl += nsmpl;
    ADXCRS_Unlock();
    for (i = 0; i < nch; i++) {
        m = (unsigned int)adxt->sjo[i]->vtbl->getNumData(adxt->sjo[i], SJ_LIN_DATA) >> 1;
        if (m >= nmax) {
            nmax = m;
        }
    }
    if (nmax + ADXRNA_GetNumData(adxt->rna) - adxt->pad_nsmpl <= 0) {
        ADXRNA_SetTransSw(adxt->rna, 0);
        ADXRNA_SetPlaySw(adxt->rna, 0);
        PS2RNA_SetStopFlag(adxt->rna, 1);
        adxt->stat = ADXT_STAT_PLAYEND;
    }
}

void adxt_stat_playend(AdxtObj *adxt)
{
}

/* Restarts a handle from the start of its input. */
void adxt_RcvrReplay(AdxtObj *adxt)
{
    int i;

    ADXCRS_Lock();
    ADXRNA_SetTransSw(adxt->rna, 0);
    ADXRNA_SetPlaySw(adxt->rna, 0);
    ADXSJD_Stop(adxt->sjd);
    ADXCRS_Unlock();
    if (adxt->stm != 0) {
        ADXSTM_Stop(adxt->stm);
        adxt->sji->vtbl->reset(adxt->sji);
    }
    ADXCRS_Lock();
    for (i = 0; i < adxt->maxnch; i++) {
        adxt->sjo[i]->vtbl->reset(adxt->sjo[i]);
    }
    if (adxt->stm != 0) {
        ADXSTM_Seek(adxt->stm, 0);
        ADXSTM_Start(adxt->stm);
    }
    adxt_start_sj(adxt, adxt->sji);
    ADXCRS_Unlock();
}

/* Error watchdog: flags a stalled decoder or a starved input (5 seconds of server calls, 20 before
 * playback) and, by the auto-recovery mode, stops or restarts the handle; the same for a read error. */
void adxt_ExecErrChk(AdxtObj *adxt)
{
    int stat;
    int pos;
    int n;

    stat = adxt->stat;
    if (stat == ADXT_STAT_PLAYING && adxt->pause_flag == 0 && ADXSJD_GetStat(adxt->sjd) != stat) {
        pos = ADXSJD_GetDecNumSmpl(adxt->sjd);
        if (adxt->edecpos == pos) {
            adxt->edeccnt++;
            if (adxt->svrfreq * 5 < adxt->edeccnt) {
                adxt->ercode = ADXT_ERR_SNDBLK;
            }
        } else {
            adxt->edeccnt = 0;
        }
        adxt->edecpos = pos;
        if (adxt->ercode != ADXT_ERR_OK) {
            if (adxt->autorcvr == ADXT_RMODE_STOP || adxt->autorcvr == ADXT_RMODE_REPLAY) {
                ADXT_Stop(adxt);
            }
            if (adxt->autorcvr != ADXT_RMODE_NOACT) {
                adxt->ercode = ADXT_ERR_OK;
                adxt->edeccnt = 0;
            }
        }
    } else {
        adxt->edeccnt = 0;
    }
    if (stat >= ADXT_STAT_DECINFO && stat <= ADXT_STAT_PLAYING && adxt->pause_flag == 0
        && ADXSJD_GetStat(adxt->sjd) != ADXSJD_STAT_DECEND) {
        n = (adxt->sji != 0) ? adxt->sji->vtbl->getNumData(adxt->sji, SJ_LIN_DATA) : 0;
        if (n < 64) {
            adxt->eshrtcnt++;
            if (stat == ADXT_STAT_PLAYING) {
                if (adxt->svrfreq * 5 < adxt->eshrtcnt) {
                    adxt->ercode = ADXT_ERR_SHRTBUF;
                }
            } else {
                if (adxt->svrfreq * 20 < adxt->eshrtcnt) {
                    adxt->ercode = ADXT_ERR_SHRTBUF;
                }
            }
            if (adxt->ercode != ADXT_ERR_OK) {
                if (adxt->autorcvr == ADXT_RMODE_STOP) {
                    ADXT_Stop(adxt);
                } else if (adxt->autorcvr == ADXT_RMODE_REPLAY) {
                    adxt_RcvrReplay(adxt);
                }
                if (adxt->autorcvr != ADXT_RMODE_NOACT) {
                    adxt->ercode = ADXT_ERR_OK;
                    adxt->eshrtcnt = 0;
                }
            }
        } else {
            adxt->eshrtcnt = 0;
        }
    } else {
        adxt->eshrtcnt = 0;
    }
    if (adxt->stm != 0 && ADXSTM_GetStat(adxt->stm) == ADXSTM_STAT_ERROR) {
        if (adxt->autorcvr == ADXT_RMODE_STOP) {
            ADXT_Stop(adxt);
        } else if (adxt->autorcvr == ADXT_RMODE_REPLAY) {
            adxt_RcvrReplay(adxt);
        }
        if (adxt->autorcvr != ADXT_RMODE_NOACT) {
            adxt->ercode = ADXT_ERR_OK;
            adxt->eshrtcnt = 0;
        }
    }
}

/* A read error of the stream or of the seamless list puts the handle in state ERROR. */
void adxt_ExecRdErrChk(AdxtObj *adxt)
{
    if (adxt->stm != 0 && ADXSTM_GetStat(adxt->stm) == ADXSTM_STAT_ERROR) {
        adxt->ercode = ADXT_ERR_SHRTBUF;
        adxt->stat = ADXT_STAT_ERROR;
    }
    if (adxt->lsc != 0 && LSC_GetStat(adxt->lsc) == LSC_STAT_ERROR) {
        adxt->ercode = ADXT_ERR_SHRTBUF;
        adxt->stat = ADXT_STAT_ERROR;
    }
}

/* Once the whole file has been read, the decoder is told no more data follows. */
void adxt_ExecRdCompChk(AdxtObj *adxt)
{
    if (adxt->stm == 0) {
        return;
    }
    if (ADXT_GetStat(adxt) == ADXT_STAT_STOP) {
        return;
    }
    switch (adxt->pmode) {
    case ADXT_PMODE_FNAME:
    case ADXT_PMODE_AFS:
        if (ADXSTM_GetStat(adxt->stm) == ADXSTM_STAT_READEND) {
            ADXSJD_TermSupply(adxt->sjd);
        }
        break;
    case ADXT_PMODE_MEM:
        ADXSJD_TermSupply(adxt->sjd);
        break;
    case ADXT_PMODE_SJ:
    case ADXT_PMODE_SLFILE:
        break;
    }
}

/* One server step of a handle: its state, then the read checks. */
void ADXT_ExecHndl(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080842_ADXT_ExecHndl_parameter_error);
        return;
    }
    if (adxt->stat == ADXT_STAT_PLAYING) {
        adxt_stat_playing(adxt);
    } else if (adxt->stat == ADXT_STAT_DECINFO) {
        adxt_stat_decinfo(adxt);
    } else if (adxt->stat == ADXT_STAT_PREP) {
        adxt_stat_prep(adxt);
    } else if (adxt->stat == ADXT_STAT_DECEND) {
        adxt_stat_decend(adxt);
    } else if (adxt->stat == ADXT_STAT_PLAYEND) {
        adxt_stat_playend(adxt);
    }
    adxt_ExecRdCompChk(adxt);
    adxt_ExecRdErrChk(adxt);
}

/* Whether a disc read is in flight for the handle's stream (or its seamless list's stream). */
int ADXT_GetStatRead(AdxtObj *adxt)
{
    if (adxt == 0) {
        return 0;
    }
    if (adxt->stm == 0) {
        if (adxt->lsc == 0) {
            return 0;
        }
        if (adxt->lsc->stm != 0) {
            return ADXSTM_GetStatRead(adxt->lsc->stm);
        }
        return 0;
    }
    return ADXSTM_GetStatRead(adxt->stm);
}
