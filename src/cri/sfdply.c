#include "dw4/cri/sfdply.h"
#include "dw4/cri/sj.h"
#include "dw4/cri/mcp.h"
#include "dw4/cri/mps.h"

typedef void (*SfdCntFn)(SfdPly *h, int arg, int *counter);
typedef void (*SfdTmrFn)(SfdPly *h, int arg, SfdTimer *tmr);

extern int DAT_004f5020[];
extern void (*sfply_vbin_nest)(SfdPly *h, int value);
extern SfdPly *sfply_handles[8];
extern int sfply_sys_stat;
extern unsigned int DAT_004beb20;
extern SfdCond sfd_lib;
extern int DAT_004bead4;
extern void (*DAT_004beb18)(SfdPtsm *ptsm);

int sfd_ReportError();
int SFLIB_CheckHn(SfdPly *h);
int FUN_002b0338();
void FUN_002af428(void);
int SFTIM_SetSpeed(SfdPly *h, int value);
int SFAOAP_SetSpeed(SfdPly *h, int value);
void SFD_SetCond(SfdPly *h, int id, int value);
void FUN_002ae398(void);
long FUN_002b5a10(void);
void FUN_002afbc8(void *acc, long time);
void SFSEE_ExecServer(SfdPly *h);
int SFTRN_CallTrSetup(SfdPly *h, int state);
int sftrn_GetFlagA(SfdPly *h, int id);
int sftrn_GetFlagB(SfdPly *h, int id);
int FUN_002b03e8(SfdPly *h, int id);
int SFBUF_GetRTot(SfdPly *h, int ch);
int SFBUF_GetWTot(SfdPly *h, int ch);
void SFSEE_FixAvPlay(SfdPly *h, int req1, int req2);
void SFSET_SetCond(SfdPly *h, int id, int value);
int SFSET_GetCond(SfdPly *h, int id);
int FUN_002b5b38(void);
void sfd_Lock(void *lock);
void sfd_Unlock(void *lock);
int UTY_MulDiv(int a, int b, int c);
int SFBUF_RingGetDataSiz(SfdPly *h, int id);
int SFBUF_GetTermFlg(SfdPly *h, int id);
void SFBUF_SetTermFlg(SfdPly *h, int id, int value);
int SFTIM_GetTime(SfdPly *h, int *pos, int *len);
int SFTIM_GetTimeSub(SfdPly *h, int *pos, int *len);
int SFTIM_IsStagnant(SfdPly *h);
int SFD_CmpTime(int a, int b, int c, int d);
int UTY_CmpTime(int a, int b, int c, int d);
void SFHDS_InitFhd(void *blk);
void SFHDS_FinishFhd(void *blk);
void sfd_ClearErr(SfdErrBlk *err);
void SFTIM_InitHn(SfdPly *h, SfdD28 *d);
int SFBUF_InitHn(SfdPly *h, SfdStmEnt *ent, SfdCrePrm *prm);
void SFTRN_InitHn(SfdPly *h, SfdF28 *f, SfdCrePrm *prm, int arg);
void SFSEE_InitHn(SfdRecSlot *slot);
void FUN_002afba8(void *acc);
void SFBUF_DestroySj(SfdPly *h);
int FUN_002a32b8(SfdPly *h, char *buf, int size);
void FUN_002a3340(SfdPly *h, char *buf, int size);
void SFD_SetErrFn(SfdPly *h, SfdErrFn fn, void *obj);
void SFD_SetUsrTimeFn(SfdPly *h, SfdTimeFn fn);
void SFD_SetExtClockFn(SfdPly *h, SfdTimeFn fn, int wrap, void *obj);
void SFD_SetUsrIsSkipFn(SfdPly *h, int (*fn)());
int SFD_EntrySeek(SfdPly *h, SfdRec *rec);
void SFD_SetByteRate(SfdPly *h, int a);
void SFD_SetFileSize(SfdPly *h, int a);
void SFD_SetTotTime(SfdPly *h, int a, int b);
void SFD_SetSeekPos(SfdPly *h, int a);
int FUN_002ac6e8(SfdPly *h, SfdItem *data, int size);
void SFBUF_SetSupplySj(SfdPly *h, int value);

long FUN_002aa3d0(SfdPly *h, unsigned int mode);
long FUN_002aa460(SfdPly *h, int mode);
long FUN_002aa4c8(SfdPly *h, int value);
int FUN_002aa538(SfdPly *h);
void sfply_ChkCondDfl(void);
int SFD_IsHnSvrWait(SfdPly *h);
void sfply_ExecOne(SfdPly *h);
void FUN_002aa980(SfdPly *h);
int FUN_002aa9a8(SfdPly *h);
int sfply_StatStop(SfdPly *h);
int sfply_StatPrep(SfdPly *h);
int sfply_IsPrepEnd(SfdPly *h);
void FUN_002aab60(SfdPly *h);
void sfply_FixAvPlay(SfdPly *h);
void sfply_AdjustSyncMode(SfdPly *h);
void FUN_002aacc0(SfdPly *h);
int sfply_StatStby(SfdPly *h);
int sfply_StatPlay(SfdPly *h);
int sfply_StatFin(SfdPly *h);
int sfply_IsStartSync(SfdPly *h);
long sfply_ChkBpa(SfdPly *h);
int sfply_IsBpaOn(SfdPly *h);
int sfply_IsBpaOff(SfdPly *h);
int sfply_IsAnyoneTerm(SfdPly *h);
int sfply_EnoughViData(SfdPly *h);
int FUN_002ab370(SfdPly *h);
int sfply_ChkFin(SfdPly *h);
int sfply_IsEtime(SfdPly *h);
int sfply_IsEtrg(SfdPly *h);
int sfply_IsStagnant(SfdPly *h);
int sfply_IsPlayTimeAutoStop(SfdPly *h);
int FUN_002ab680(SfdPly *h);
int SFPLY_DecideSvrStat(void);
int FUN_002ab810(SfdCrePrm *prm);
int FUN_002ab878(void);
SfdPly *sfply_InitHn(SfdCrePrm *prm, int arg);
void sfply_InitMvInf(SfdRec48 *rec);
void sfply_InitPlyInf(SfdTimer *tmr);
void FUN_002abbc0(SfdSub24 *sub);
void sfply_InitTmrInf(SfdTable *tbl);
int FUN_002abd00(SfdPly *h);
int sfply_TrDestroy(SfdPly *h);
int sfply_Start(SfdPly *h);
long sfply_TrStart(SfdPly *h);
int SFPLY_Stop(SfdPly *h);
void SFPLY_SetResetFlg(int on);
int sfply_TrStop(SfdPly *h);
int FUN_002abfd8(SfdPly *h);
int SFD_GetWritePtr(SfdPly *h, SfdBufStat *inf);
int SFD_AddWritePtr(SfdPly *h, int a, int b);
int SFD_TermSupply(SfdPly *h);

int SFD_GetPaStat(SfdPly *h) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000141);
        return 0;
    }
    return h->pause;
}

int SFD_Pause(SfdPly *h, int sw) {
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
    FUN_002aa3d0(h, mode);
    /* matching construct: permuter-found do-while(0) around the flag store; without it the beqz delay
       slot takes the error code's ori instead of mode = 1 (2 words) */
    do {
        h->pending = 1;
    } while (0);
}

long FUN_002aa3d0(SfdPly *h, unsigned int mode) {
    long r = 0;
    switch (mode) {
    case 2:
        if (h->stat == 4) r = FUN_002aa460(h, mode);
        break;
    case 1:
        if (++h->pauseCnt == mode) r = FUN_002aa460(h, mode);
        break;
    case 0:
        if (--h->pauseCnt == 0) r = FUN_002aa460(h, 0);
        break;
    }
    return r;
}

long FUN_002aa460(SfdPly *h, int mode) {
    if (h->reqStat != 3 && h->reqStat != 4) {
        return 0;
    }
    FUN_002af428();
    return FUN_002aa4c8(h, mode);
}

/* matching construct: hand — the long return type (callee returns int) is what keeps
   retail's plain jal instead of a sibling tail call */
long FUN_002aa4c8(SfdPly *h, int value) {
    return FUN_002b0338(h, 7, 8, value, 0);
}

void SFD_Standby(SfdPly *h) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000143);
        return;
    }
    FUN_002aa538(h);
}

int FUN_002aa538(SfdPly *h) {
    h->reqStat = 3;
    return 0;
}

int SFD_SetSpeed(SfdPly *h, int value) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000144);
    }
    SFTIM_SetSpeed(h, value);
    SFAOAP_SetSpeed(h, value);
    return 0;
}

int SFD_SetAudioCh(SfdPly *h, int value) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000145, value);
    }
    SFD_SetCond(h, 30, value);
    return 0;
}

int SFD_SetVideoCh(SfdPly *h, int value) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000146, value);
    }
    SFD_SetCond(h, 29, value);
    return 0;
}

void sfmpvps2_Init(void) {
    sfply_ChkCondDfl();
    sfply_vbin_nest = 0;
}

void sfply_ChkCondDfl(void) {
    if (DAT_004f5020[0] != 0x5A5A5A5A) {
        sfd_ReportError(0, 0xFF000201);
    }
}

void SFD_VsyncSvr(void) {
    FUN_002ae398();
}

void SFD_VbOut(void) {
}

int SFD_IsHnSvrWait(SfdPly *h) {
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

int SFD_ExecOne(SfdPly *h) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000138);
    }
    sfply_ExecOne(h);
    return 0;
}

void FUN_002aa810(void) {
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
    start = FUN_002b5a10();
    if (st >= 2 && st <= 4) {
        FUN_002aa980(h);
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
    FUN_002afbc8(h->tbl.trailer, FUN_002b5a10() - start);
}

void FUN_002aa980(SfdPly *h) {
    FUN_002aa9a8(h);
    SFSEE_ExecServer(h);
}

int FUN_002aa9a8(SfdPly *h) {
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
    FUN_002aab60(h);
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
        audio = sftrn_GetFlagA(h, 6);
        audio |= sftrn_GetFlagB(h, 6);
    }
    if (SFSET_GetCond(h, 6) == 0) {
        video = 1;
    } else {
        video = sftrn_GetFlagA(h, 7);
        video |= sftrn_GetFlagB(h, 7);
    }
    if (audio != 0 && video != 0) return 1;
    return 0;
}

void FUN_002aab60(SfdPly *h) {
    sfply_FixAvPlay(h);
    sfply_AdjustSyncMode(h);
    FUN_002aacc0(h);
}

void sfply_FixAvPlay(SfdPly *h) {
    SfdCond *c = &h->cond;
    if (c->req1 == 1 && SFBUF_GetWTot(h, 1) == 0 && SFBUF_GetRTot(h, 1) == 0) {
        c->req1 = 0;
    }
    if (c->req2 == 1 && SFBUF_GetWTot(h, 2) == 0 && SFBUF_GetRTot(h, 2) == 0) {
        c->req2 = 0;
    }
    SFSEE_FixAvPlay(h, c->req1, c->req2);
}

void sfply_AdjustSyncMode(SfdPly *h) {
    SfdCond *c = &h->cond;
    if (c->req2 == 0 && c->mode == 2) {
        SFSET_SetCond(h, 15, 1);
    }
    if (c->req1 == 0 && c->mode == 1) {
        SFSET_SetCond(h, 15, 2);
    }
}

void FUN_002aacc0(SfdPly *h) {
    SfdCond *c = &h->cond;
    unsigned int mask;
    int value;
    mask = 0;
    if (c->req2 == 1)
        mask = 1;
    if (c->req1 == 1)
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
        if (value == 0 && (FUN_002b5b38() != 0 || SFSET_GetCond(h, 72) == 0))
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
    SfdCond *c = &h->cond;
    SfdD28 *d = &h->d28;
    if (c->f56 == 0) return 1;
    if (c->req1 == 0) return 1;
    if (d->f688 != 0) return 1;
    if (d->f716 >= c->f180) return 1;
    return sfply_IsEtrg(h) != 0;
}

long sfply_ChkBpa(SfdPly *h) {
    char lock[16];
    SfdTimer *t = &h->tmr;
    long result;
    sfd_Lock(lock);
    result = 0;
    if (t->active == 0) {
        if (sfply_IsBpaOn(h) != 0) {
            t->active = 1;
            t->activations++;
            result = FUN_002aa3d0(h, 1);
        }
    } else if (sfply_IsBpaOff(h) != 0) {
        t->active = 0;
        result = FUN_002aa3d0(h, 0);
    }
    sfd_Unlock(lock);
    return result;
}

int sfply_IsBpaOn(SfdPly *h) {
    SfdTimer *t = &h->tmr;
    int v[2];
    SfdD28 *d;
    int a, b;
    if (SFSET_GetCond(h, 67) == 0) return 0;
    if (SFSET_GetCond(h, 15) == 0) return 0;
    if (h->pause != 0) return 0;
    if (h->stat != 4) return 0;
    if (sfply_IsAnyoneTerm(h) != 0) return 0;
    if (SFSET_GetCond(h, 5) == 1 && t->f36 == 0) return 0;
    if (SFSET_GetCond(h, 6) == 1 && SFBUF_RingGetDataSiz(h, 2) > 0) return 0;
    if (FUN_002b03e8(h, 1) != 0 && SFBUF_RingGetDataSiz(h, 0) > 0) return 0;
    if (SFSET_GetCond(h, 5) == 1 && sfply_EnoughViData(h) != 0) return 0;
    SFTIM_GetTime(h, &v[0], &v[1]);
    d = &h->d28;
    a = d->f648;
    b = d->f644;
    b -= UTY_MulDiv(SFSET_GetCond(h, 68), a, 1000000);
    if (v[0] <= 0 || b <= 0) return 0;
    return SFD_CmpTime(v[0], v[1], b, a) == 0;
}

int sfply_IsBpaOff(SfdPly *h) {
    int v[2];
    SfdD28 *d;
    int a, b;
    if (sfply_IsAnyoneTerm(h) != 0) return 1;
    if (SFSET_GetCond(h, 5) == 1 && sfply_EnoughViData(h) != 0) return 1;
    if (SFSET_GetCond(h, 6) == 1 && FUN_002ab370(h) != 0) return 1;
    SFTIM_GetTime(h, &v[0], &v[1]);
    d = &h->d28;
    a = d->f648;
    b = d->f644;
    return SFD_CmpTime(v[0], v[1], b - UTY_MulDiv(SFSET_GetCond(h, 69), a, 1000000), a) != 0;
}

int sfply_IsAnyoneTerm(SfdPly *h) {
    int result;
    unsigned int ch;
    if (SFSET_GetCond(h, 5) != 0 && sftrn_GetFlagB(h, 6) != 0) {
        return 1;
    }
    if (SFSET_GetCond(h, 6) != 0 && sftrn_GetFlagB(h, 7) != 0) {
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
    SfdStmInf *e = &h->ent[h->f28.f152].info;
    SjObj *sj = e->sj;
    int v = sj->vtbl->getNumData(sj, 1);
    if (v < e->size * 80 / 100 && v < SFSET_GetCond(h, 70)) {
        return 0;
    }
    return 1;
}

int FUN_002ab370(SfdPly *h) {
    SfdStmInf *e = &h->ent[h->f28.f220].info;
    SjObj *sj = e->sj;
    if (sj->vtbl->getNumData(sj, 1) < e->size * 80 / 100) {
        return 0;
    }
    return 1;
}

int sfply_ChkFin(SfdPly *h) {
    if (sfply_IsEtime(h) != 0 || sfply_IsEtrg(h) != 0 || sfply_IsStagnant(h) != 0 || sfply_IsPlayTimeAutoStop(h) != 0) {
        return FUN_002ab680(h);
    }
    return 0;
}

int sfply_IsEtime(SfdPly *h) {
    SfdCond *c = &h->cond;
    int first;
    int second;
    int request;
    int value;
    request = c->request;
    value = c->value;
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
    SfdCond *c = &h->cond;
    int check6;
    int check7;
    unsigned int mode;
    int result;
    if (c->req2 == 0 && c->req1 == 0) {
        return 1;
    }
    check6 = sftrn_GetFlagB(h, 6);
    check7 = sftrn_GetFlagB(h, 7);
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
    SfdTimer *t = &h->tmr;
    if (h->stat != 4 || h->pause == 1 || t->active == 1) return 0;
    return SFTIM_IsStagnant(h) != 0;
}

int sfply_IsPlayTimeAutoStop(SfdPly *h) {
    SfdTimer *t = &h->tmr;
    int v[2];
    if (h->stat != 4 || h->pause == 1 || t->active == 1) return 0;
    if (SFTIM_GetTimeSub(h, &v[0], &v[1]) != 0) return 0;
    if (v[0] < 0) return 0;
    return SFD_CmpTime(SFSET_GetCond(h, 54), 1000, v[0], v[1]) != 0;
}

int FUN_002ab680(SfdPly *h) {
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

SfdPly *FUN_002ab778(SfdCrePrm *prm, int arg) {
    SfdPly **handles = sfply_handles;
    int slot;
    SfdPly *h;
    if (FUN_002ab810(prm) != 0) {
        return 0;
    }
    slot = FUN_002ab878();
    if (slot == -1) {
        sfd_ReportError(0, 0xFF000206);
        return 0;
    }
    h = sfply_InitHn(prm, arg);
    handles[slot] = h;
    return h;
}

int FUN_002ab810(SfdCrePrm *prm) {
    if (prm->f4 == 0) {
        return sfd_ReportError(0, 0xFF000204);
    }
    if (prm->workSize < 0x3718U) {
        return sfd_ReportError(0, 0xFF000205);
    }
    return 0;
}

int FUN_002ab878(void) {
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
    if (DAT_004beb20 != 0 && DAT_004beb20 != wksiz)
        return 0;
    DAT_004beb20 = wksiz;
    UTY_MemsetDword(work, 0, ndw);
    h = (SfdPly *)(((unsigned int)work + 31) & ~31);
    h->stat = h->reqStat = 0;
    prm->f4 = (char *)(((unsigned int)prm->f4 + 31) & ~31);
    h->cre = *prm;
    h->pause = 0;
    h->pending = 1;
    h->pauseCnt = 0;
    SFHDS_InitFhd(h->blk120);
    sfply_InitMvInf(&h->rec2316);
    sfply_InitPlyInf(&h->tmr);
    sfply_InitTmrInf(&h->tbl);
    sfd_ClearErr(&h->err);
    MEM_Copy(&h->cond, &sfd_lib, sizeof(h->cond));
    MEM_Copy(&h->cond2, &sfd_lib, sizeof(h->cond2));
    SFTIM_InitHn(h, &h->d28);
    if (SFBUF_InitHn(h, h->ent, prm) != 0)
        return 0;
    SFTRN_InitHn(h, &h->f28, prm, arg);
    SFSEE_InitHn(&h->recSlot);
    if (FUN_002abd00(h) != 0)
        return 0;
    h->reqStat = 1;
    h->stat = 1;
    return h;
}

void sfply_InitMvInf(SfdRec48 *rec) {
    UTY_MemsetDword(rec, 0, 16);
    rec->f0 = 0;
    rec->f4 = 0;
    rec->f8 = 0;
    rec->f12 = 0;
    rec->f16 = 0;
    rec->f20 = 0;
    rec->f24 = 0;
    rec->f32 = 0;
    rec->enabled = 1;
    rec->id36 = -1;
    rec->id40 = -1;
    rec->id44 = -1;
}

void sfply_InitPlyInf(SfdTimer *tmr) {
    UTY_MemsetDword(tmr, 0, 40);
    tmr->count = 0;
    tmr->count2 = 0;
    tmr->f8 = 0;
    tmr->f12 = 0;
    tmr->f16 = 0;
    tmr->f24 = 0;
    tmr->active = 0;
    tmr->activations = 0;
    tmr->f36 = 0;
    tmr->f40 = 0;
    tmr->f44 = 0;
    FUN_002abbc0(&tmr->sub[0]);
    FUN_002abbc0(&tmr->sub[1]);
    FUN_002abbc0(&tmr->sub[2]);
    FUN_002abbc0(&tmr->sub[3]);
}

void FUN_002abbc0(SfdSub24 *sub) {
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    sub->f0 = 0;
    sub->f8 = 0;
    sub->f16 = 0;
}

void sfply_InitTmrInf(SfdTable *tbl) {
    SfdTblEnt *e;
    int i;
    UTY_MemsetDword(tbl, 0, 48);
    e = tbl->ent;
    for (i = 4; i >= 0; i--) {
        FUN_002afba8(e++);
    }
    FUN_002afba8(tbl->trailer);
}

void SFPLY_AddDecPic(SfdPly *h, int delta, int arg) {
    int *counter = &h->tmr.count;
    SfdCntFn fn;
    *counter += delta;
    fn = (SfdCntFn)SFSET_GetCond(h, 36);
    if (fn != 0) {
        fn(h, arg, counter);
    }
}

void SFPLY_AddSkipPic(SfdPly *h, int delta, int arg) {
    SfdTimer *t = &h->tmr;
    SfdTmrFn fn;
    t->count2 += delta;
    fn = (SfdTmrFn)SFSET_GetCond(h, 37);
    if (fn != 0) {
        fn(h, arg, t);
    }
}

int FUN_002abd00(SfdPly *h) {
    return SFTRN_CallTrSetup(h, 3);
}

int SFD_Destroy(SfdPly *h) {
    int result;
    int i;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000131);
    }
    SFPLY_Stop(h);
    SFHDS_FinishFhd(h->blk120);
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

int SFD_Start(SfdPly *h) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000132);
    }
    if (SFSET_GetCond(h, 47) == 1) {
        FUN_002aa538(h);
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
    return FUN_002b0338(h, 7, 6, 0, 0);
}

/* matching construct: implicit-int return (declared int, no value returned) — epilogue order */
int SFD_Stop(SfdPly *h) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000133);
        return;
    }
    SFPLY_Stop(h);
    h->pending = 1;
}

int SFPLY_Stop(SfdPly *h) {
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
    result = FUN_002abfd8(h);
    SFPLY_SetResetFlg(0);
    return result;
}

void SFPLY_SetResetFlg(int on) {
    DAT_004bead4 = on;
}

int SFPLY_GetResetFlg(void) {
    return DAT_004bead4;
}

int sfply_TrStop(SfdPly *h) {
    int result;
    if (h->stat == 4) {
        result = FUN_002b0338(h, 7, 7, 0, 0);
        if (result != 0) {
            return result;
        }
    }
    h->stat = 1;
    h->reqStat = 1;
    return 0;
}

int FUN_002abfd8(SfdPly *h) {
    int nmpv;
    SfdCrePrm prm;
    SfdBufStat inf;
    SfdCond cond;
    char mpvcond[64];
    SfdPtsm ptsm;
    int keepsup;
    int supadr = 0;
    SfdErrFn errfn;
    void *errobj;
    SfdTimeFn usrtimefn;
    SfdTimeFn extfn;
    int extwrap;
    void *extobj;
    int (*isskipfn)();
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
    keepsup = h->cond.f32;
    if (keepsup) {
        SFD_GetWritePtr(h, &inf);
        supadr = inf.tailLen;
    }
    SFHDS_FinishFhd(h->blk120);
    SFBUF_DestroySj(h);
    errfn = h->err.fn;
    errobj = h->err.obj;
    ptsm = h->d28.ptsm;
    usrtimefn = h->d28.timefn[4];
    extfn = h->d28.extClockFn;
    extwrap = h->d28.extClockWrap;
    extobj = h->d28.extClockObj;
    isskipfn = h->d28.isSkipFn;
    speed = h->d28.speed;
    see = h->recSlot.rec;
    if (see != 0) {
        byterate = see->f3536;
        fsize = see->f3524;
        tottime = see->f3528;
        tunit = see->f3532;
        seekpos = see->f3540;
    } else {
        seekpos = 0;
        tunit = 0;
        tottime = 0;
        fsize = 0;
        byterate = 0;
    }
    ptsque = &h->ent[1].ring;
    ptssiz = ptsque->size * sizeof(SfdItem);
    ptsent = ptsque->items;
    nmpv = FUN_002a32b8(h, mpvcond, sizeof(mpvcond));
    ret = sfply_TrDestroy(h);
    if (ret != 0) {
        return ret;
    }
    MEM_Copy(&cond, &h->cond2, sizeof(cond));
    h = sfply_InitHn(&prm, 0);
    if (h == 0) {
        return sfd_ReportError(0, 0xFF000202);
    }
    MEM_Copy(&h->cond, &cond, sizeof(cond));
    MEM_Copy(&h->cond2, &cond, sizeof(cond));
    FUN_002a3340(h, mpvcond, nmpv);
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
        h->d28.ptsm = ptsm;
        if (DAT_004beb18 != 0) {
            DAT_004beb18(&ptsm);
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
        FUN_002ac6e8(h, ptsent, ptssiz);
    }
    return 0;
}

int SFD_GetWritePtr(SfdPly *h, SfdBufStat *inf) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000134);
    }
    return FUN_002b0338(h, 0, 9, inf, 0);
}

int SFD_AddWritePtr(SfdPly *h, int a, int b) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000135);
    }
    return FUN_002b0338(h, 0, 10, a, b);
}

int SFD_TermSupply(SfdPly *h) {
    int id;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000135);
    }
    id = h->f28.f20;
    if (SFBUF_GetTermFlg(h, id) == 1) {
        return 0;
    }
    SFBUF_SetTermFlg(h, id, 1);
    h->pending = 1;
    return 0;
}

int SFPLY_IsTermSupply(SfdPly *h) {
    return SFBUF_GetTermFlg(h, h->f28.f20) != 0;
}

int SFD_GetFrm(SfdPly *h, int *out) {
    int result;
    int value;
    *out = 0;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000136, 11, out, 0);
    }
    result = FUN_002b0338(h, 6, 11, out, 0);
    value = *out;
    if (value != 0) {
        h->tmr.f24 = 1;
    }
    if (sfply_vbin_nest != 0) {
        sfply_vbin_nest(h, value);
    }
    return result;
}

void SFD_RelFrm(SfdPly *h, int value) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000137);
        return;
    }
    h->tmr.f24 = 0;
    FUN_002b0338(h, 6, 12, value, 0);
}

void SFD_SetSupplySj(SfdPly *h, int value) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000139);
        return;
    }
    SFBUF_SetSupplySj(h, value);
}
