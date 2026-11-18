#include "dw4/cri/sfdply.h"
#include "dw4/cri/sj.h"
#include "dw4/cri/mcp.h"
#include "dw4/cri/mps.h"
#include "dw4/cri/uty.h"
#include "dw4/cri/sfd.h"

typedef void (*SfdCntFn)(SfdPly *h, int arg, int *counter);
typedef void (*SfdTmrFn)(SfdPly *h, int arg, SfdPlyInf *tmr);

extern int SFPLY_cond_dfl_guard[];
extern void (*sfply_vbin_nest)(SfdPly *h, int value);
extern SfdPly *sfply_handles[8];
extern int sfply_sys_stat;
extern unsigned int sfply_last_hnctrl_wksiz;


extern int sfply_reset_flg;
extern void (*SFPLY_ResetPtsm)(SfdPtsm *ptsm);


long SFPL2_Pause(SfdPly *h, unsigned int mode);
long sfpl2_PauseExec(SfdPly *h, int mode);
long sfpl2_TrPause(SfdPly *h, int value);
void sfply_ChkCondDfl(void);
void sfply_ExecOne(SfdPly *h);
void sfply_ExecOneSub(SfdPly *h);
int sfply_TrExecServer(SfdPly *h);
int sfply_StatStop(SfdPly *h);
int sfply_StatPrep(SfdPly *h);
int sfply_IsPrepEnd(SfdPly *h);
void sfply_AdjustPrepEnd(SfdPly *h);
void sfply_FixAvPlay(SfdPly *h);
void sfply_AdjustSyncMode(SfdPly *h);
void sfply_AdjustEtrg(SfdPly *h);
int sfply_StatStby(SfdPly *h);
int sfply_StatPlay(SfdPly *h);
int sfply_StatFin(SfdPly *h);
int sfply_IsStartSync(SfdPly *h);
long sfply_ChkBpa(SfdPly *h);
int sfply_IsBpaOn(SfdPly *h);
int sfply_IsBpaOff(SfdPly *h);
int sfply_IsAnyoneTerm(SfdPly *h);
int sfply_EnoughViData(SfdPly *h);
int sfply_EnoughAiData(SfdPly *h);
int sfply_ChkFin(SfdPly *h);
int sfply_IsEtime(SfdPly *h);
int sfply_IsEtrg(SfdPly *h);
int sfply_IsStagnant(SfdPly *h);
int sfply_IsPlayTimeAutoStop(SfdPly *h);
int sfply_Fin(SfdPly *h);
int sfply_ChkCrePara(SfdCrePrm *prm);
int sfply_SearchFreeHn(void);
SfdPly *sfply_InitHn(SfdCrePrm *prm, int arg);
void sfply_InitMvInf(SfdMvInf *rec);
void sfply_InitPlyInf(SfdPlyInf *tmr);
void sfply_InitFlowCnt(long long *cnt);
void sfply_InitTmrInf(SfdTmrInf *tmr);
int sfply_TrCreate(SfdPly *h);
int sfply_TrDestroy(SfdPly *h);
int sfply_Start(SfdPly *h);
long sfply_TrStart(SfdPly *h);
void SFPLY_SetResetFlg(int on);
int sfply_TrStop(SfdPly *h);
int sfply_ResetHn(SfdPly *h);

int SFD_GetPaStat(void *sfd) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000141);
        return 0;
    }
    return h->pause;
}

int SFD_Pause(void *sfd, int sw) {
    SfdPly *h = sfd;
    int mode;
    int pause;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000142);
    }
    pause = h->pause;
    mode = 1;
    if (sw == 0) {
        if (pause == 0) {
            return 0;
        }
        mode = 0;
    } else if (pause != 0) {
        mode = 2;
    }
    h->pause = sw;
    SFPL2_Pause(h, mode);
    /* matching construct: permuter-found do-while(0) around the flag store; without it the beqz delay
       slot takes the error code's ori instead of mode = 1 (2 words) */
    do {
        h->pending = 1;
    } while (0);
}

long SFPL2_Pause(SfdPly *h, unsigned int mode) {
    long r = 0;
    switch (mode) {
    case 2:
        if (h->stat == 4) r = sfpl2_PauseExec(h, mode);
        break;
    case 1:
        if (++h->pauseCnt == mode) r = sfpl2_PauseExec(h, mode);
        break;
    case 0:
        if (--h->pauseCnt == 0) r = sfpl2_PauseExec(h, 0);
        break;
    }
    return r;
}

long sfpl2_PauseExec(SfdPly *h, int mode) {
    if (h->reqStat != 3 && h->reqStat != 4) {
        return 0;
    }
    SFTIM_Pause(h, mode);
    return sfpl2_TrPause(h, mode);
}

/* matching construct: hand — the long return type (callee returns int) is what keeps
   retail's plain jal instead of a sibling tail call */
long sfpl2_TrPause(SfdPly *h, int value) {
    return SFTRN_CallTrtTrif(h, 7, 8, value, 0);
}

int SFD_Standby(void *sfd) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000143);
    }
    return SFPL2_Standby(h);
}

int SFPL2_Standby(void *sfd) {
    SfdPly *h = sfd;
    h->reqStat = 3;
    return 0;
}

int SFD_SetSpeed(void *sfd, int value) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000144);
    }
    SFTIM_SetSpeed(h, value);
    SFAOAP_SetSpeed(h, value);
    return 0;
}

int SFD_SetAudioCh(void *sfd, int value) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000145);
    }
    SFD_SetCond(h, 30, value);
    return 0;
}

int SFD_SetVideoCh(void *sfd, int value) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000146);
    }
    SFD_SetCond(h, 29, value);
    return 0;
}

void sfmpvps2_Init(void) {
    sfply_ChkCondDfl();
    sfply_vbin_nest = 0;
}

void sfply_ChkCondDfl(void) {
    if (SFPLY_cond_dfl_guard[0] != 0x5A5A5A5A) {
        sfd_ReportError(0, 0xFF000201);
    }
}

void SFD_VsyncSvr(void) {
    SFTIM_VbIn();
}

void SFD_VbOut(void) {
}

int SFD_IsHnSvrWait(void *sfd) {
    SfdPly *h = sfd;
    if (h->stat < 1 || h->stat > 4) return 1;
    return h->pending == 0;
}

int SFD_IsSvrDone(void) {
    SfdPly **slot = sfply_handles;
    int i;
    for (i = 0; i < 8; i++) {
        SfdPly *h = *slot++;
        if (h != 0 && SFD_IsHnSvrWait(h) == 0) {
            return 0;
        }
    }
    return 1;
}

int SFD_ExecOne(void *sfd) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000138);
    }
    sfply_ExecOne(h);
    return 0;
}

void SFD_ExecServer(void) {
    SfdPly **slot = sfply_handles;
    int i;
    for (i = 0; i < 8; i++) {
        SfdPly *h = *slot++;
        if (h != 0) {
            sfply_ExecOne(h);
        }
    }
    SFPLY_DecideSvrStat();
}

void sfply_ExecOne(SfdPly *h) {
    int st = h->stat;
    long start;
    if (st < 1 || st > 4) return;
    if (h->pending == 0) return;
    *(volatile int *)&h->pending = 0;
    start = UTY_GetTmr();
    if (st >= 2 && st <= 4) {
        sfply_ExecOneSub(h);
    }
    st = h->stat;
    switch (st) {
    case 0:
        break;
    case 1:
        st = sfply_StatStop(h);
        break;
    case 2:
        st = sfply_StatPrep(h);
        break;
    case 3:
        st = sfply_StatStby(h);
        break;
    case 4:
        st = sfply_StatPlay(h);
        break;
    case 6:
        st = sfply_StatFin(h);
        break;
    }
    h->stat = st;
    SFTMR_AddTsum(&h->tmr.tsum[5], UTY_GetTmr() - start);
}

void sfply_ExecOneSub(SfdPly *h) {
    sfply_TrExecServer(h);
    SFSEE_ExecServer(h);
}

int sfply_TrExecServer(SfdPly *h) {
    return SFTRN_CallTrSetup(h, 2);
}

int sfply_StatStop(SfdPly *h) {
    int req = h->reqStat;
    int st = h->stat;
    if (req >= 2 && (req < 5 || req == 6)) {
        st = 2;
    }
    return st;
}

int sfply_StatPrep(SfdPly *h) {
    int st = h->stat;
    int req = h->reqStat;
    if (sfply_IsPrepEnd(h) == 0) {
        return st;
    }
    sfply_AdjustPrepEnd(h);
    switch (req) {
    case 2:
        st = 2;
        break;
    case 3:
        st = 3;
        break;
    case 4:
    case 6:
        if (sfply_IsStartSync(h) != 0) {
            st = 4;
            sfply_TrStart(h);
        } else {
            st = 3;
        }
        break;
    }
    return st;
}

int sfply_IsPrepEnd(SfdPly *h) {
    int audio, video;
    if (SFSET_GetCond(h, 5) == 0) {
        audio = 1;
    } else {
        audio = SFTRN_GetPrepFlg(h, 6);
        audio |= SFTRN_GetTermFlg(h, 6);
    }
    if (SFSET_GetCond(h, 6) == 0) {
        video = 1;
    } else {
        video = SFTRN_GetPrepFlg(h, 7);
        video |= SFTRN_GetTermFlg(h, 7);
    }
    if (audio != 0 && video != 0) return 1;
    return 0;
}

void sfply_AdjustPrepEnd(SfdPly *h) {
    sfply_FixAvPlay(h);
    sfply_AdjustSyncMode(h);
    sfply_AdjustEtrg(h);
}

void sfply_FixAvPlay(SfdPly *h) {
    int *c = h->cond;
    if (c[SFD_COND_VIDEO] == 1 && SFBUF_GetWTot(h, 1) == 0 && SFBUF_GetRTot(h, 1) == 0) {
        c[SFD_COND_VIDEO] = 0;
    }
    if (c[SFD_COND_AUDIO] == 1 && SFBUF_GetWTot(h, 2) == 0 && SFBUF_GetRTot(h, 2) == 0) {
        c[SFD_COND_AUDIO] = 0;
    }
    SFSEE_FixAvPlay(h, c[SFD_COND_VIDEO], c[SFD_COND_AUDIO]);
}

void sfply_AdjustSyncMode(SfdPly *h) {
    int *c = h->cond;
    if (c[SFD_COND_AUDIO] == 0 && c[SFD_COND_SYNCMODE] == 2) {
        SFSET_SetCond(h, SFD_COND_SYNCMODE, 1);
    }
    if (c[SFD_COND_VIDEO] == 0 && c[SFD_COND_SYNCMODE] == 1) {
        SFSET_SetCond(h, SFD_COND_SYNCMODE, 2);
    }
}

void sfply_AdjustEtrg(SfdPly *h) {
    int *c = h->cond;
    unsigned int mask;
    int value;
    mask = 0;
    if (c[SFD_COND_AUDIO] == 1)
        mask = 1;
    if (c[SFD_COND_VIDEO] == 1)
        mask |= 2;
    switch (mask) {
    case 1:
        value = 1;
        break;
    case 2:
        value = 2;
        break;
    case 3:
        value = SFSET_GetCond(h, 25);
        if (value == 0 && (UTY_IsTmrVoid() != 0 || SFSET_GetCond(h, 72) == 0))
            value = 3;
        break;
    default:
        value = 3;
        break;
    }
    SFSET_SetCond(h, 25, value);
}

int sfply_StatStby(SfdPly *h) {
    int st = h->stat;
    switch (h->reqStat) {
    case 2:
        st = 2;
        break;
    case 3:
        st = 3;
        break;
    case 4:
    case 6:
        if (sfply_IsStartSync(h) != 0) {
            st = 4;
            sfply_TrStart(h);
        }
        break;
    }
    return st;
}

int sfply_StatPlay(SfdPly *h) {
    int req;
    int st;
    if (sfply_ChkFin(h) != 0 || sfply_ChkBpa(h) != 0) {
        return h->stat;
    }
    req = h->reqStat;
    st = h->stat;
    if (req >= 2) {
        if (req < 5) {
            return st;
        }
        if (req == 6) {
            st = 6;
        }
    }
    return st;
}

int sfply_StatFin(SfdPly *h) {
    return h->stat;
}

int sfply_IsStartSync(SfdPly *h) {
    int *c = h->cond;
    SfdTim *d = &h->tim;
    if (c[14] == 0) return 1;
    if (c[SFD_COND_VIDEO] == 0) return 1;
    if (d->disp_sync_cnt != 0) return 1;
    if (d->count >= c[45]) return 1;
    return sfply_IsEtrg(h) != 0;
}

long sfply_ChkBpa(SfdPly *h) {
    char lock[16];
    SfdPlyInf *t = &h->plyInf;
    long result;
    sfd_Lock(lock);
    result = 0;
    if (t->bpaActive == 0) {
        if (sfply_IsBpaOn(h) != 0) {
            t->bpaActive = 1;
            t->noSupply++;
            result = SFPL2_Pause(h, 1);
        }
    } else if (sfply_IsBpaOff(h) != 0) {
        t->bpaActive = 0;
        result = SFPL2_Pause(h, 0);
    }
    sfd_Unlock(lock);
    return result;
}

int sfply_IsBpaOn(SfdPly *h) {
    SfdPlyInf *t = &h->plyInf;
    int v[2];
    SfdTim *d;
    int a, b;
    if (SFSET_GetCond(h, 67) == 0) return 0;
    if (SFSET_GetCond(h, 15) == 0) return 0;
    if (h->pause != 0) return 0;
    if (h->stat != 4) return 0;
    if (sfply_IsAnyoneTerm(h) != 0) return 0;
    if (SFSET_GetCond(h, 5) == 1 && t->vidShort == 0) return 0;
    if (SFSET_GetCond(h, 6) == 1 && SFBUF_RingGetDataSiz(h, 2) > 0) return 0;
    if (SFTRN_IsSetup(h, 1) != 0 && SFBUF_RingGetDataSiz(h, 0) > 0) return 0;
    if (SFSET_GetCond(h, 5) == 1 && sfply_EnoughViData(h) != 0) return 0;
    SFTIM_GetTime(h, &v[0], &v[1]);
    d = &h->tim;
    a = d->dec_unit;
    b = d->dec_time;
    b -= UTY_MulDiv(SFSET_GetCond(h, 68), a, 1000000);
    if (v[0] <= 0 || b <= 0) return 0;
    return SFD_CmpTime(v[0], v[1], b, a) == 0;
}

int sfply_IsBpaOff(SfdPly *h) {
    int v[2];
    SfdTim *d;
    int a, b;
    if (sfply_IsAnyoneTerm(h) != 0) return 1;
    if (SFSET_GetCond(h, 5) == 1 && sfply_EnoughViData(h) != 0) return 1;
    if (SFSET_GetCond(h, 6) == 1 && sfply_EnoughAiData(h) != 0) return 1;
    SFTIM_GetTime(h, &v[0], &v[1]);
    d = &h->tim;
    a = d->dec_unit;
    b = d->dec_time;
    return SFD_CmpTime(v[0], v[1], b - UTY_MulDiv(SFSET_GetCond(h, 69), a, 1000000), a) != 0;
}

int sfply_IsAnyoneTerm(SfdPly *h) {
    int result;
    unsigned int ch;
    if (SFSET_GetCond(h, 5) != 0 && SFTRN_GetTermFlg(h, 6) != 0) {
        return 1;
    }
    if (SFSET_GetCond(h, 6) != 0 && SFTRN_GetTermFlg(h, 7) != 0) {
        return 1;
    }
    for (ch = 0; ch < 8; ch++) {
        result = SFBUF_GetTermFlg(h, ch);
        if (result != 0) {
            return 1;
        }
    }
    return result;
}

int sfply_EnoughViData(SfdPly *h) {
    SfdBufInf *e = &h->buf[h->trn[2].bufIn].u.ring.sup;
    SfdSj *sj = e->sj;
    int v = sj->vtbl->getNumData(sj, 1);
    if (v < e->size * 80 / 100 && v < SFSET_GetCond(h, 70)) {
        return 0;
    }
    return 1;
}

int sfply_EnoughAiData(SfdPly *h) {
    SfdBufInf *e = &h->buf[h->trn[3].bufIn].u.ring.sup;
    SfdSj *sj = e->sj;
    if (sj->vtbl->getNumData(sj, 1) < e->size * 80 / 100) {
        return 0;
    }
    return 1;
}

int sfply_ChkFin(SfdPly *h) {
    if (sfply_IsEtime(h) != 0 || sfply_IsEtrg(h) != 0 || sfply_IsStagnant(h) != 0 || sfply_IsPlayTimeAutoStop(h) != 0) {
        return sfply_Fin(h);
    }
    return 0;
}

int sfply_IsEtime(SfdPly *h) {
    int *c = h->cond;
    int first;
    int second;
    int request;
    int value;
    request = c[SFD_COND_ETIME];
    value = c[SFD_COND_ETUNIT];
    if (request == -4) {
        return 0;
    }
    SFTIM_GetTime(h, &first, &second);
    if (first < 0) {
        return 0;
    }
    return UTY_CmpTime(first, second, request, value) == 0;
}

int sfply_IsEtrg(SfdPly *h) {
    int *c = h->cond;
    int check6;
    int check7;
    unsigned int mode;
    int result;
    if (c[SFD_COND_AUDIO] == 0 && c[SFD_COND_VIDEO] == 0) {
        return 1;
    }
    check6 = SFTRN_GetTermFlg(h, 6);
    check7 = SFTRN_GetTermFlg(h, 7);
    mode = SFSET_GetCond(h, 25);
    result = 0;
    switch (mode) {
    case 0:
        result = check7 & check6;
        break;
    case 1:
        result = check7;
        break;
    case 2:
        result = check6;
        break;
    case 3:
        result = check7 | check6;
        break;
    }
    return result;
}

int sfply_IsStagnant(SfdPly *h) {
    SfdPlyInf *t = &h->plyInf;
    if (h->stat != 4 || h->pause == 1 || t->bpaActive == 1) return 0;
    return SFTIM_IsStagnant(h) != 0;
}

int sfply_IsPlayTimeAutoStop(SfdPly *h) {
    SfdPlyInf *t = &h->plyInf;
    int v[2];
    if (h->stat != 4 || h->pause == 1 || t->bpaActive == 1) return 0;
    if (SFTIM_GetTimeSub(h, &v[0], &v[1]) != 0) return 0;
    if (v[0] < 0) return 0;
    return SFD_CmpTime(SFSET_GetCond(h, 54), 1000, v[0], v[1]) != 0;
}

int sfply_Fin(SfdPly *h) {
    int ok = sfply_TrStop(h);
    if (ok == 0) {
        h->reqStat = 6;
    }
    return ok;
}

int SFPLY_DecideSvrStat(void) {
    int count[3];
    int lock;
    SfdPly **slot;
    int i;
    int kind;
    sfd_Lock(&lock);
    count[0] = 0;
    count[1] = 0;
    count[2] = 0;
    slot = sfply_handles;
    for (i = 0; i < 8; i++) {
        SfdPly *h = *slot++;
        if (h != 0) {
            int st = h->stat;
            if (st == 0) {
                kind = 0;
            } else if (st == 6 || st < 0) {
                kind = 2;
            } else {
                kind = 1;
            }
            count[kind]++;
        }
    }
    if (count[1] != 0) {
        kind = 1;
    } else if (count[2] != 0) {
        kind = 2;
    } else {
        kind = 0;
    }
    sfply_sys_stat = kind;
    sfd_Unlock(&lock);
    return kind;
}

void *SFD_Create(SfdCrePrm *prm, int arg) {
    SfdPly **handles = sfply_handles;
    int slot;
    SfdPly *h;
    if (sfply_ChkCrePara(prm) != 0) {
        return 0;
    }
    slot = sfply_SearchFreeHn();
    if (slot == -1) {
        sfd_ReportError(0, 0xFF000206);
        return 0;
    }
    h = sfply_InitHn(prm, arg);
    handles[slot] = h;
    return h;
}

int sfply_ChkCrePara(SfdCrePrm *prm) {
    if (prm->bufWork == 0) {
        return sfd_ReportError(0, 0xFF000204);
    }
    if (prm->workSize < 0x3718U) {
        return sfd_ReportError(0, 0xFF000205);
    }
    return 0;
}

int sfply_SearchFreeHn(void) {
    SfdPly **slot = sfply_handles;
    int i;
    for (i = 0; i < 8; i++) {
        if (*slot++ == 0) {
            return i;
        }
    }
    return -1;
}

/* Builds a player handle in the caller's work area: the work size must stay the same for every handle
 * (at most 28208 bytes), and the handle starts at the first 32-byte boundary of the work. */
SfdPly *sfply_InitHn(SfdCrePrm *prm, int arg) {
    SfdPly *h;
    char *work = prm->work;
    unsigned int wksiz = prm->workSize;
    unsigned int ndw = wksiz >> 2;

    if (work == 0)
        return 0;
    if (wksiz == 0 || wksiz > 28208)
        return 0;
    if (sfply_last_hnctrl_wksiz != 0 && sfply_last_hnctrl_wksiz != wksiz)
        return 0;
    sfply_last_hnctrl_wksiz = wksiz;
    UTY_MemsetDword(work, 0, ndw);
    h = (SfdPly *)(((unsigned int)work + 31) & ~31);
    h->stat = h->reqStat = 0;
    prm->bufWork = (char *)(((unsigned int)prm->bufWork + 31) & ~31);
    h->cre = *prm;
    h->pause = 0;
    h->pending = 1;
    h->pauseCnt = 0;
    SFHDS_InitFhd(&h->hdr);
    sfply_InitMvInf(&h->mvInf);
    sfply_InitPlyInf(&h->plyInf);
    sfply_InitTmrInf(&h->tmr);
    sfd_ClearErr(&h->err);
    MEM_Copy(h->cond, sfd_lib.cond, sizeof(h->cond));
    MEM_Copy(h->cond2, sfd_lib.cond, sizeof(h->cond2));
    SFTIM_InitHn(h, &h->tim);
    if (SFBUF_InitHn(h, h->buf, prm) != 0)
        return 0;
    SFTRN_InitHn(h, h->trn, prm, arg);
    SFSEE_InitHn(&h->see);
    if (sfply_TrCreate(h) != 0)
        return 0;
    h->reqStat = 1;
    h->stat = 1;
    return h;
}

void sfply_InitMvInf(SfdMvInf *rec) {
    UTY_MemsetDword(rec, 0, 16);
    rec->width = 0;
    rec->height = 0;
    rec->mbWidth = 0;
    rec->mbHeight = 0;
    rec->bitRate = 0;
    rec->frameRate = 0;
    rec->muxRate = 0;
    rec->vbvSize = 0;
    rec->fixedFlag = 1;
    rec->audioBound = -1;
    rec->videoBound = -1;
    rec->privateBound = -1;
}

void sfply_InitPlyInf(SfdPlyInf *inf) {
    UTY_MemsetDword(inf, 0, 40);
    inf->numTotalDec = 0;
    inf->numSkip = 0;
    inf->rsv[0] = 0;
    inf->rsv[1] = 0;
    inf->numSkipEmptyB = 0;
    inf->frmOut = 0;
    inf->bpaActive = 0;
    inf->noSupply = 0;
    inf->vidShort = 0;
    inf->noFreeFrm = 0;
    inf->lockCnt = 0;
    sfply_InitFlowCnt(&inf->sysFlow);
    sfply_InitFlowCnt(&inf->vidFlow);
    sfply_InitFlowCnt(&inf->audInWr);
    sfply_InitFlowCnt(&inf->audSjWr);
}

void sfply_InitFlowCnt(long long *cnt) {
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    cnt[0] = 0;
    cnt[1] = 0;
    cnt[2] = 0;
}

void sfply_InitTmrInf(SfdTmrInf *tmr) {
    SfdTsum *e;
    int i;
    UTY_MemsetDword(tmr, 0, 48);
    e = tmr->tsum;
    for (i = 4; i >= 0; i--) {
        SFTMR_InitTsum(e++);
    }
    SFTMR_InitTsum(&tmr->tsum[5]);
}

void SFPLY_AddDecPic(SfdPly *h, int delta, int arg) {
    int *counter = &h->plyInf.numTotalDec;
    SfdCntFn fn;
    *counter += delta;
    fn = (SfdCntFn)SFSET_GetCond(h, 36);
    if (fn != 0) {
        fn(h, arg, counter);
    }
}

void SFPLY_AddSkipPic(void *sfd, int delta, int arg) {
    SfdPly *h = sfd;
    SfdPlyInf *t = &h->plyInf;
    SfdTmrFn fn;
    t->numSkip += delta;
    fn = (SfdTmrFn)SFSET_GetCond(h, 37);
    if (fn != 0) {
        fn(h, arg, t);
    }
}

int sfply_TrCreate(SfdPly *h) {
    return SFTRN_CallTrSetup(h, 3);
}

int SFD_Destroy(void *sfd) {
    SfdPly *h = sfd;
    int result;
    int i;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000131);
    }
    SFPLY_Stop(h);
    SFHDS_FinishFhd(&h->hdr);
    SFBUF_DestroySj(h);
    result = sfply_TrDestroy(h);
    for (i = 0; i < 8; i++) {
        if (sfply_handles[i] == h) {
            sfply_handles[i] = 0;
        }
    }
    return result;
}

int sfply_TrDestroy(SfdPly *h) {
    h->stat = 0;
    h->reqStat = 0;
    return SFTRN_CallTrSetup(h, 4);
}

int SFD_Start(void *sfd) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000132);
    }
    if (SFSET_GetCond(h, 47) == 1) {
        SFPL2_Standby(h);
    } else {
        sfply_Start(h);
    }
    h->pending = 1;
}

int sfply_Start(SfdPly *h) {
    h->reqStat = 4;
    return 0;
}

/* matching construct: hand — the long return type (callee returns int) is what keeps
   retail's plain jal instead of a sibling tail call */
long sfply_TrStart(SfdPly *h) {
    return SFTRN_CallTrtTrif(h, 7, 6, 0, 0);
}

/* matching construct: implicit-int return (declared int, no value returned) — epilogue order */
int SFD_Stop(void *sfd) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000133);
        return;
    }
    SFPLY_Stop(h);
    h->pending = 1;
}

int SFPLY_Stop(void *sfd) {
    SfdPly *h = sfd;
    int result;
    if (h->stat == 1) {
        return 0;
    }
    result = sfply_TrStop(h);
    if (result != 0) {
        return result;
    }
    h->reqStat = 0;
    h->stat = 0;
    SFPLY_SetResetFlg(1);
    result = sfply_ResetHn(h);
    SFPLY_SetResetFlg(0);
    return result;
}

void SFPLY_SetResetFlg(int on) {
    sfply_reset_flg = on;
}

int SFPLY_GetResetFlg(void) {
    return sfply_reset_flg;
}

int sfply_TrStop(SfdPly *h) {
    int result;
    if (h->stat == 4) {
        result = SFTRN_CallTrtTrif(h, 7, 7, 0, 0);
        if (result != 0) {
            return result;
        }
    }
    h->stat = 1;
    h->reqStat = 1;
    return 0;
}

int sfply_ResetHn(SfdPly *h) {
    int nmpv;
    SfdCrePrm prm;
    SfdBufStat inf;
    int cond[SFD_COND_NUM];
    int mpvcond[16];
    SfdPtsm ptsm;
    int keepsup;
    int supadr = 0;
    SfdErrFn errfn;
    void *errobj;
    SfdTimeFn usrtimefn;
    SfdExtClockFn extfn;
    int extwrap;
    int extobj;
    SfdIsSkipFn isskipfn;
    int speed;
    SfdRec *see;
    int byterate;
    int fsize;
    int tottime;
    int tunit;
    int seekpos;
    SfdRing *ptsque;
    SfdItem *ptsent;
    int ptssiz;
    int ret;

    prm = h->cre;
    keepsup = h->cond[SFD_COND_KEEPSUP];
    if (keepsup) {
        SFD_GetWritePtr(h, &inf);
        supadr = inf.tailLen;
    }
    SFHDS_FinishFhd(&h->hdr);
    SFBUF_DestroySj(h);
    errfn = h->err.func;
    errobj = h->err.obj;
    ptsm = h->tim.ptsm;
    usrtimefn = h->tim.timefn[4];
    extfn = h->tim.clock_get;
    extwrap = h->tim.clock_wrap;
    extobj = h->tim.clock_ctx;
    isskipfn = h->tim.isSkipFn;
    speed = h->tim.speed;
    see = h->see.rec;
    if (see != 0) {
        byterate = see->byterate;
        fsize = see->fsize;
        tottime = see->tottime;
        tunit = see->tunit;
        seekpos = see->seekpos;
    } else {
        seekpos = 0;
        tunit = 0;
        tottime = 0;
        fsize = 0;
        byterate = 0;
    }
    ptsque = &h->buf[1].u.ring.ptsque;
    ptssiz = ptsque->size * sizeof(SfdItem);
    ptsent = ptsque->items;
    nmpv = SFMPV_SaveCond(h, mpvcond, sizeof(mpvcond));
    ret = sfply_TrDestroy(h);
    if (ret != 0) {
        return ret;
    }
    MEM_Copy(cond, h->cond2, sizeof(cond));
    h = sfply_InitHn(&prm, 0);
    if (h == 0) {
        return sfd_ReportError(0, 0xFF000202);
    }
    MEM_Copy(h->cond, cond, sizeof(cond));
    MEM_Copy(h->cond2, cond, sizeof(cond));
    SFMPV_RestoreCond(h, mpvcond, nmpv);
    if (keepsup) {
        ret = SFD_GetWritePtr(h, &inf);
        if (ret != 0) {
            return ret;
        }
        ret = SFD_AddWritePtr(h, supadr, inf.tailLen);
        if (ret != 0) {
            return ret;
        }
        SFD_TermSupply(h);
    }
    if (errfn != 0) {
        SFD_SetErrFn(h, errfn, errobj);
    }
    if (usrtimefn != 0) {
        SFD_SetUsrTimeFn(h, usrtimefn);
    }
    if (extfn != 0) {
        SFD_SetExtClockFn(h, extfn, extwrap, extobj);
    }
    if (isskipfn != 0) {
        SFD_SetUsrIsSkipFn(h, isskipfn);
    }
    if (speed != 1000) {
        SFD_SetSpeed(h, speed);
    }
    if (ptsm.f0 != 0) {
        h->tim.ptsm = ptsm;
        if (SFPLY_ResetPtsm != 0) {
            SFPLY_ResetPtsm(&ptsm);
        }
    }
    if (see != 0) {
        SFD_EntrySeek(h, see);
        SFD_SetByteRate(h, byterate);
        SFD_SetFileSize(h, fsize);
        SFD_SetTotTime(h, tottime, tunit);
        SFD_SetSeekPos(h, seekpos);
    }
    if (ptsent != 0) {
        SFD_SetVideoPts(h, ptsent, ptssiz);
    }
    return 0;
}

int SFD_GetWritePtr(void *sfd, SfdBufStat *inf) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000134);
    }
    return SFTRN_CallTrtTrif(h, 0, 9, (int)inf, 0);
}

int SFD_AddWritePtr(void *sfd, int a, int b) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000135);
    }
    return SFTRN_CallTrtTrif(h, 0, 10, a, b);
}

int SFD_TermSupply(void *sfd) {
    SfdPly *h = sfd;
    int id;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000135);
    }
    id = h->trn[0].bufOut[0];
    if (SFBUF_GetTermFlg(h, id) == 1) {
        return 0;
    }
    SFBUF_SetTermFlg(h, id, 1);
    h->pending = 1;
    return 0;
}

int SFPLY_IsTermSupply(SfdPly *h) {
    return SFBUF_GetTermFlg(h, h->trn[0].bufOut[0]) != 0;
}

int SFD_GetFrm(void *sfd, int *out) {
    SfdPly *h = sfd;
    int result;
    int value;
    *out = 0;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000136);
    }
    result = SFTRN_CallTrtTrif(h, 6, 11, (int)out, 0);
    value = *out;
    if (value != 0) {
        h->plyInf.frmOut = 1;
    }
    if (sfply_vbin_nest != 0) {
        sfply_vbin_nest(h, value);
    }
    return result;
}

int SFD_RelFrm(void *sfd, int value) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000137);
    }
    h->plyInf.frmOut = 0;
    return SFTRN_CallTrtTrif(h, 6, 12, value, 0);
}

int SFD_SetSupplySj(void *sfd, struct SfdBufInf *inf) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000139);
    }
    return SFBUF_SetSupplySj(h, inf);
}
