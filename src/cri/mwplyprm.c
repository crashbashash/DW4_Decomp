/* MWPLY settings and getters: the mwPly/mwSfd calls that check the player handle and forward to
 * the SFD decoder (ply->sfd), the ADXT audio handle or the file stream (ply->stm). */
#include "dw4/cri/mwply.h"
#include "dw4/cri/lsc.h"

/* SFD decoder parameters set and read through SFD_SetCond / SFD_GetCondDef */
#define SFD_COND_VIDEO_SW 5
#define SFD_COND_AUDIO_SW 6
#define SFD_COND_EMPTY_BPIC_SKIP 7
#define SFD_COND_SYNC_MODE 15
#define SFD_COND_LIMIT_TIME 54
#define SFD_COND_TIMER_CH 61
#define SFD_COND_SYNC_EXT 71

#define MWSFD_SYNC_NONE 0
#define MWSFD_SYNC_VSYNC 1
#define MWSFD_SYNC_AUDIO 2
#define MWSFD_SYNC_EXT 3

/* the decoder's header information (SFD_GetHnHdrInf) */
typedef struct SfdHdrInf {
    int f0[9];
    int numAudioCh;  /* 36 */
    int numVideoCh;  /* 40 */
    int f44[5];
} SfdHdrInf;

/* the decoder's playback information (SFD_GetPlyInf) */
typedef struct SfdPlyInf {
    int numTotalDec;    /* 0 */
    int numSkip;        /* 4: skipped decodes, empty B pictures included */
    int f8;
    int f12;
    int numSkipEmptyB;  /* 16 */
    int f20;
    int f24;
    int f28;
    int stat8;          /* 32 */
    int f36;
    int f40;
    int f44;
    long long flow[12]; /* 48: the input flow counters */
    int f144[4];
} SfdPlyInf;

/* mwPlyGetPlyInf */
typedef struct MwsfdPlyInf {
    int numDropFrm;
    int numSkipDec;
    int numSkipDisp;
    int numSkipEmptyB;
    int stat8;
} MwsfdPlyInf;

/* mwPlyGetFlowInf */
typedef struct MwsfdFlowInf {
    long long flow[12];
} MwsfdFlowInf;

void mwsfd_Error(const char *msg);
void MWSFLIB_SetErrCode(int code);
int mwPlyGetNumSkipDisp(MwsfdPly *ply);
void MWSFRNA_SetOutVol(MwsfdPly *ply, int vol);
int MWSFRNA_GetOutVol(MwsfdPly *ply);
void MWSFRNA_SetOutPan(MwsfdPly *ply, int channel, int pan);
int MWSFRNA_GetOutPan(MwsfdPly *ply, int channel);
void MWSFLSC_SetFlowLimit(MwsfdPly *ply, int limit);
void mwsst_SetOutVol(MwsfdSst *sst, int vol);
int mwsst_GetOutVol(MwsfdSst *sst);
int MWSTM_SetRdSct(void *stm, int value);
int MWSTM_SetTrSct(void *stm);
void MWSTM_SetFlowLimit(void *stm, int limit, int cap);
void MWSTM_GetFlowLimit(void *stm, int *limit, int *cap);
void MWSTM_GetFsizeByte(void *stm, int *len);
int SFD_GetVideoCh(void *sfd);
int SFD_GetAudioCh(void *sfd);
void SFD_SetMpvCond(void *sfd, int param, int value);
int SFD_GetNumDecPool(void *sfd, int *num);
void SFD_SetSpeed(void *sfd, int speed);
int SFD_SetAudioCh(void *sfd, int ch);
int SFD_SetVideoCh(void *sfd, int ch);
void SFD_SetCond(void *sfd, int param, int value);
int SFD_GetCondDef(void *sfd, int param, int *value);
void SFD_GetHnHdrInf(void *sfd, SfdHdrInf *inf);
void SFD_GetPlyInf(void *sfd, SfdPlyInf *inf);
int SFD_GetTime(void *sfd, int *count, int *unit);
int SFD_GetHnStat(void *sfd);
void SFD_GetInputBufStat(void *sfd, SfdBufStat *stat);
int SFD_SetStmObject(void *sfd, int id, void *object, int (*cb)(void *obj, int arg), void *cbObj);
int MWSTM_GetStatRead(void *stm);

int MWSFD_IsEnableHndl(MwsfdPly *ply);
void *mwPlyGetSfdHn(MwsfdPly *ply);
void *MWSFD_GetAdxtHn(MwsfdPly *ply);
int mwPlyGetNumSkipDec(MwsfdPly *ply);
void mwply_SetPicSkip(MwsfdPly *ply, int mode, int param);
void mwply_GetSfdPlyInf(MwsfdPly *ply, SfdPlyInf *inf);
void mwply_GetHdrInf(MwsfdPly *ply, SfdHdrInf *inf);
void MWSFD_SetCond(MwsfdPly *ply, int param, int value);
void MWSFD_SetFlowLimit(MwsfdPly *ply, int limit, int cap);
int mwPlyGetNumSkipEmptyB(MwsfdPly *ply);

void mwPlySetAudioSw(MwsfdPly *ply, int sw) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122617 mwPlySetAudioSw: handle is invalid.");
        return;
    }
    SFD_SetCond(ply->sfd, SFD_COND_AUDIO_SW, sw);
}

void mwPlySetVideoSw(MwsfdPly *ply, int sw) {
    SFD_SetCond(ply->sfd, SFD_COND_VIDEO_SW, sw);
}

void *mwPlyGetSfdHn(MwsfdPly *ply) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122640: mwPlyGetSfdHn: handle is invalid.");
        return 0;
    }
    return ply->sfd;
}

void *mwPlyGetAdxtHn(MwsfdPly *ply) {
    if (!MWSFD_IsEnableHndl(ply)) {
        mwsfd_Error("E1122639: mwPlyGetAdxtHn: handle is invalid.");
        return 0;
    }
    return MWSFD_GetAdxtHn(ply);
}

int mwPlyGetNumDropFrm(MwsfdPly *ply) {
    int numSkipDec;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E202232: mwPlyGetNumDropFrm: handle is invalid.");
        return 0;
    }
    numSkipDec = mwPlyGetNumSkipDec(ply);
    return numSkipDec + mwPlyGetNumSkipDisp(ply);
}

int mwPlyGetNumSkipDec(MwsfdPly *ply) {
    SfdPlyInf inf;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122619: mwPlyGetNumSkipDec: handle is invalid.");
        return 0;
    }
    SFD_GetPlyInf(mwPlyGetSfdHn(ply), &inf);
    return inf.numSkip - inf.numSkipEmptyB;
}

void mwPlySetBpicSkip(MwsfdPly *ply, int mode) {
    mwply_SetPicSkip(ply, mode, 3);
}

void mwPlySetPpicSkip(MwsfdPly *ply, int mode) {
    mwply_SetPicSkip(ply, mode, 4);
}

void mwply_SetPicSkip(MwsfdPly *ply, int mode, int param) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122628: mwPlySetBpicSkip mwPlySetPpicSkip: handle is invalid.");
        return;
    }
    SFD_SetCond(ply->sfd, param, mode != 1);
}

void mwPlySetAudioCh(MwsfdPly *ply, int ch) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122616 mwPlySetAudioCh: handle is invalid.");
        return;
    }
    if (SFD_SetAudioCh(ply->sfd, ch) != 0) {
        mwsfd_Error("E10911A mwPlySetAudioCh: Invalid ch no.");
        return; /* matching construct: manual — the explicit return makes this call a tail jump */
    }
}

int mwPlyGetAudioCh(MwsfdPly *ply) {
    return SFD_GetAudioCh(ply->sfd);
}

int mwPlyGetNumAudioCh(MwsfdPly *ply) {
    SfdHdrInf inf;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E2080801 mwPlyGetNumAudioCh: handle is invalid.");
        return -1;
    }
    mwply_GetHdrInf(ply, &inf);
    return inf.numAudioCh;
}

void mwPlySetVideoCh(MwsfdPly *ply, int ch) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E2080601 mwPlySetVideoCh: handle is invalid.");
        return;
    }
    if (SFD_SetVideoCh(ply->sfd, ch) != 0) {
        mwsfd_Error("E2080602 mwPlySetVideoCh: Invalid ch no.");
        return; /* matching construct: manual — the explicit return makes this call a tail jump */
    }
}

int mwPlyGetVideoCh(MwsfdPly *ply) {
    return SFD_GetVideoCh(ply->sfd);
}

int mwPlyGetNumVideoCh(MwsfdPly *ply) {
    SfdHdrInf inf;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E2080802 mwPlyGetNumVideoCh: handle is invalid.");
        return -1;
    }
    mwply_GetHdrInf(ply, &inf);
    return inf.numVideoCh;
}

void mwply_GetSfdPlyInf(MwsfdPly *ply, SfdPlyInf *inf) {
    SFD_GetPlyInf(ply->sfd, inf);
}

void mwply_GetHdrInf(MwsfdPly *ply, SfdHdrInf *inf) {
    SFD_GetHnHdrInf(ply->sfd, inf);
}

void MWSFD_SetCond(MwsfdPly *ply, int param, int value) {
    void *sfd = 0;

    if (ply != 0) {
        sfd = ply->sfd;
    }
    SFD_SetCond(sfd, param, value);
}

void MWSFD_GetCond(MwsfdPly *ply, int param, int *value) {
    void *sfd = 0;

    if (ply != 0) {
        sfd = ply->sfd;
    }
    SFD_GetCondDef(sfd, param, value);
}

void *MWSFD_GetStmHn(MwsfdPly *ply) {
    return ply->stm;
}

int MWSFD_GetInputSjBufSize(MwsfdPly *ply) {
    return ply->inputBufSize;
}

void MWSFD_SetFlowLimit(MwsfdPly *ply, int limit, int cap) {
    MWSTM_SetFlowLimit(ply->stm, limit, cap);
    MWSFLSC_SetFlowLimit(ply, limit);
}

void mwply_GetFlowLimit(MwsfdPly *ply, int *limit, int *cap) {
    MWSTM_GetFlowLimit(ply->stm, limit, cap);
}

int mwply_SetReqRdSize(MwsfdPly *ply, int value) {
    return MWSTM_SetRdSct(ply->stm, value);
}

/* the stream side does nothing and returns 0 */
int mwply_StmNop(MwsfdPly *ply) {
    return MWSTM_SetTrSct(ply->stm);
}

void mwply_SetDispLatencyTime(MwsfdPly *ply, int value) {
    SFD_SetCond(ply->sfd, 44, value);
}

int MWSFD_IsEnableHndl(MwsfdPly *ply) {
    int used = 0;

    if (ply != 0) {
        used = ply->used;
    }
    return used;
}

struct LscObj *MWSFD_GetLscHn(MwsfdPly *ply) {
    return ply->lsc;
}

void *MWSFD_GetAdxtHn(MwsfdPly *ply) {
    return ply->adxt;
}

void *MWSFD_GetSfxHn(MwsfdPly *ply) {
    return ply->sfx;
}

/* the limit is given in seconds and kept in milliseconds */
void mwPlySetLimitTime(MwsfdPly *ply, int sec) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122625: mwPlySetLimitTime: handle is invalid.");
        return;
    }
    MWSFD_SetCond(ply, SFD_COND_LIMIT_TIME, sec * 1000);
}

/* While playing, the SFD handle's state refines the player's: 4 and 6 read as playback end (2), a
 * negative state as an error (4). */
int mwSfdGetStat(MwsfdPly *ply) {
    int stat;
    int sfdStat;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFLIB_SetErrCode(-12);
        mwsfd_Error("W2004 mwSfdGetStat: handle is invalid");
        return 0;
    }
    stat = ply->stat;
    if (stat == 2) {
        sfdStat = SFD_GetHnStat(ply->sfd);
        if (sfdStat == 4 || sfdStat == 6) {
            return 2;
        }
        return (sfdStat < 0) ? 4 : 1;
    }
    return stat;
}

void mwply_SetSyncSw(MwsfdPly *ply, int on) {
    void *sfd = ply->sfd;

    if (on == 0) {
        SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 0);
        return;
    }
    if (ply->cre.type == 1) {
        SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 2);
        return;
    }
    SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 1);
}

void mwPlySetSyncMode(MwsfdPly *ply, int mode) {
    void *sfd;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122626: mwPlySetSyncMode: handle is invalid.");
        return;
    }
    sfd = ply->sfd;
    if (mode == MWSFD_SYNC_NONE) {
        SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 0);
        return;
    }
    if (mode == MWSFD_SYNC_VSYNC) {
        SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 1);
        return;
    }
    if (mode == MWSFD_SYNC_AUDIO) {
        if (ply->cre.type == 1) {
            SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 2);
            return;
        }
        SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 1);
        return;
    }
    if (mode != MWSFD_SYNC_EXT)
        return;
    SFD_SetCond(sfd, SFD_COND_SYNC_MODE, 5);
    SFD_SetCond(sfd, SFD_COND_SYNC_EXT, 1);
}

int mwPlyGetSyncMode(MwsfdPly *ply) {
    int value;
    int mode;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E2010802: mwPlyGetSyncMode: handle is invalid.");
        return -1;
    }
    SFD_GetCondDef(ply->sfd, SFD_COND_SYNC_MODE, &value);
    switch (value) {
    case 0:
        mode = MWSFD_SYNC_NONE;
        break;
    case 1:
        mode = MWSFD_SYNC_VSYNC;
        break;
    case 2:
        mode = MWSFD_SYNC_AUDIO;
        break;
    default:
        mwsfd_Error("E2010803: mwPlyGetSyncMode: mode is invalid.");
        mode = -1;
        break;
    }
    return mode;
}

int mwPlyGetNumDecPool(MwsfdPly *ply) {
    int num;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122621: mwPlyGetNumDecPool: handle is invalid.");
        return 0;
    }
    if (SFD_GetNumDecPool(ply->sfd, &num) != 0) {
        mwsfd_Error("E1121601 mwPlyGetNumDecPool");
    }
    return num;
}

int mwPlyGetNumTotalDec(MwsfdPly *ply) {
    SfdPlyInf inf;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122620: mwPlyGetNumTotalDec: handle is invalid.");
        return 0;
    }
    mwply_GetSfdPlyInf(ply, &inf);
    return inf.numTotalDec;
}

int mwply_GetInputBufLen(MwsfdPly *ply) {
    SfdBufStat stat;

    SFD_GetInputBufStat(ply->sfd, &stat);
    return stat.ck0.len + stat.ck1.len;
}

/* The time is count/unit seconds; an invalid handle, a failed read or a negative count read 0/1. */
void mwSfdGetTime(MwsfdPly *ply, int *count, int *unit) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122603 mwSfdGetTime; handle is invalid.");
        *count = 0;
        *unit = 1;
        return;
    }
    if (SFD_GetTime(ply->sfd, count, unit) != 0) {
        MWSFLIB_SetErrCode(-309);
        mwsfd_Error("E2006 mwSfdGetTime; can't get time");
        *count = 0;
        *unit = 1;
    }
    if (*count < 0) {
        *count = 0;
        *unit = 1;
    }
}

void mwPlySetFastHalfpel(MwsfdPly *ply, int value) {
    void *sfd = 0;

    if (ply != 0) {
        sfd = ply->sfd;
    }
    SFD_SetMpvCond(sfd, 3, value);
}

void mwply_SetMpvPara5(MwsfdPly *ply, int value) {
    void *sfd = 0;

    if (ply != 0) {
        sfd = ply->sfd;
    }
    SFD_SetMpvCond(sfd, 5, value);
}

void mwSfdSetOutVol(MwsfdPly *ply, int vol) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122605 mwSfdSetOutVol: handle is invalid.");
        return;
    }
    MWSFRNA_SetOutVol(ply, vol);
    mwsst_SetOutVol(&ply->sst, vol);
}

/* The ADXT volume wins unless it is 0, then the SST's. */
int mwSfdGetOutVol(MwsfdPly *ply) {
    int adxtVol, inputVol, vol;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122606 mwSfdGetOutVol: handle is invalid.");
        return 0;
    }
    adxtVol = MWSFRNA_GetOutVol(ply);
    inputVol = mwsst_GetOutVol(&ply->sst);
    if (adxtVol == inputVol) {
        vol = adxtVol;
    } else if (adxtVol != 0) {
        vol = adxtVol;
    } else {
        vol = inputVol;
    }
    return vol;
}

void mwSfdSetOutPan(MwsfdPly *ply, int channel, int pan) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122607 mwSfdSetOutPan: handle is invalid.");
        return;
    }
    MWSFRNA_SetOutPan(ply, channel, pan);
}

int mwSfdGetOutPan(MwsfdPly *ply, int channel) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122608 mwSfdGetOutPan: handle is invalid.");
        return 0;
    }
    return MWSFRNA_GetOutPan(ply, channel);
}

void mwply_SetMpvPara4(MwsfdPly *ply, int on) {
    void *sfd = 0;

    if (ply != 0) {
        sfd = ply->sfd;
    }
    if (on == 1) {
        SFD_SetMpvCond(sfd, 4, 1);
        return;
    }
    SFD_SetMpvCond(sfd, 4, 0);
}

void mwply_SetNoSkip(MwsfdPly *ply, int on) {
    void *sfd = ply->sfd;

    if (on == 1) {
        SFD_SetCond(sfd, 39, 1);
        return;
    }
    SFD_SetCond(sfd, 39, 0);
}

/* matching construct: manual — retail reads ply->sfd before the NULL test (load in the branch
 * delay slot); testing first and loading inside the branch does not match. */
void mwply_SetCntCb(MwsfdPly *ply, int value) {
    void *sfd = ply->sfd;

    if (ply != 0) {
        SFD_SetCond(sfd, 36, value);
    }
}

/* matching construct: manual — as mwply_SetCntCb. */
void mwply_SetTmrCb(MwsfdPly *ply, int value) {
    void *sfd = ply->sfd;

    if (ply != 0) {
        SFD_SetCond(sfd, 37, value);
    }
}

int mwPlyGetNumSkipEmptyB(MwsfdPly *ply) {
    SfdPlyInf inf;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122623: mwPlyGetNumSkipEmptyB: handle is invalid.");
        return 0;
    }
    mwply_GetSfdPlyInf(ply, &inf);
    return inf.numSkipEmptyB;
}

void mwPlySetEmptyBpicSkip(MwsfdPly *ply, int mode) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122627: mwPlySetEmptyBpicSkip: handle is invalid.");
        return;
    }
    SFD_SetCond(mwPlyGetSfdHn(ply), SFD_COND_EMPTY_BPIC_SKIP, mode != 1);
}

SfdSj *mwPlyGetInputSj(MwsfdPly *ply) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122624: mwPlyGetInputSj: handle is invalid.");
        return 0;
    }
    return ply->defSj;
}

void mwPlyGetPlyInf(MwsfdPly *ply, MwsfdPlyInf *out) {
    SfdPlyInf inf;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E202191: mwPlyGetPlyInf: handle is invalid.");
        return;
    }
    SFD_GetPlyInf(mwPlyGetSfdHn(ply), &inf);
    out->numDropFrm = mwPlyGetNumDropFrm(ply);
    out->numSkipDec = mwPlyGetNumSkipDec(ply);
    out->numSkipDisp = mwPlyGetNumSkipDisp(ply);
    out->numSkipEmptyB = mwPlyGetNumSkipEmptyB(ply);
    out->stat8 = inf.stat8;
}

void mwPlyGetFlowInf(MwsfdPly *ply, MwsfdFlowInf *out) {
    SfdPlyInf inf;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122643: mwPlyGetFlowInf: handle is invalid.");
        return;
    }
    SFD_GetPlyInf(mwPlyGetSfdHn(ply), &inf);
    out->flow[0] = inf.flow[0];
    out->flow[1] = inf.flow[1];
    out->flow[2] = inf.flow[2];
    out->flow[3] = inf.flow[3];
    out->flow[4] = inf.flow[4];
    out->flow[5] = inf.flow[5];
    out->flow[6] = inf.flow[6];
    out->flow[7] = inf.flow[7];
    out->flow[8] = inf.flow[8];
    out->flow[9] = inf.flow[9];
    out->flow[10] = inf.flow[10];
    out->flow[11] = inf.flow[11];
}

/* The stream's byte rate (maxBps / 8, rounded down to whole 2 KiB sectors) times `ratio`, capped
 * at the input buffer size. */
void mwply_SetFlowLimitRatio(MwsfdPly *ply, float ratio) {
    int cap = ply->inputBufSize;
    int limit = (float)((ply->cre.maxBps / 16384) << 11) * ratio;

    if (cap < limit) {
        limit = cap;
    }
    MWSFD_SetFlowLimit(ply, limit, cap);
}

int mwply_GetFileLen(MwsfdPly *ply) {
    int len;
    void *stm = ply->stm;

    if (stm == 0) {
        return 0;
    }
    MWSTM_GetFsizeByte(stm, &len);
    return len;
}

/* The read status of the player's file stream, or else of the stream of its link stream controller;
 * 0 without a handle or a stream. */
int mwply_GetStmStatRead(MwsfdPly *ply) {
    void *stm;
    struct LscObj *lsc;

    if (ply == 0) {
        return 0;
    }
    stm = ply->stm;
    lsc = ply->lsc;
    if (stm == 0) {
        if (lsc == 0) {
            return 0;
        }
        return lsc->stm ? MWSTM_GetStatRead(lsc->stm) : 0;
    }
    return MWSTM_GetStatRead(stm);
}

void mwPlySetSpeed(MwsfdPly *ply, int speed) {
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E302251: mwPlySetSpeed: handle is invalid.");
        return;
    }
    SFD_SetSpeed(mwPlyGetSfdHn(ply), speed);
}

/* The speed is kept in thousandths, rounded half up. */
void mwPlySetFloatSpeed(MwsfdPly *ply, float speed) {
    void *sfd;
    float rounded;
    int milli;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E211051: mwPlySetFloatSpeed: handle is invalid.");
        return;
    }
    sfd = mwPlyGetSfdHn(ply);
    rounded = speed * 1000.0f + 0.5f;
    milli = (int)rounded;
    SFD_SetSpeed(sfd, milli - (rounded < (float)milli));
}

void mwply_SetVideoAutoOff(MwsfdPly *ply, int value) {
    SFD_SetCond(ply->sfd, 79, value);
}

void mwply_SetAudioAutoOff(MwsfdPly *ply, int value) {
    SFD_SetCond(ply->sfd, 80, value);
}

void mwply_SetCond73(MwsfdPly *ply, int value) {
    SFD_SetCond(ply->sfd, 73, value);
}

void mwply_SetSystemEndcodeSkip(MwsfdPly *ply, int value) {
    SFD_SetCond(ply->sfd, 56, value);
}

void mwply_SetVideoEndcodeSkip(MwsfdPly *ply, int value) {
    SFD_SetCond(ply->sfd, 57, value);
}

void mwply_SetSeqHdrData(MwsfdPly *ply, int a, int b) {
    SFD_SetCond(ply->sfd, 93, a);
    SFD_SetCond(ply->sfd, 94, b);
}

void mwply_SetSeqHdrCbFn(MwsfdPly *ply, int a, int b) {
    SFD_SetCond(ply->sfd, 78, b);
    SFD_SetCond(ply->sfd, 77, a);
}

void mwply_SetPesCbFn(MwsfdPly *ply, int a, int b) {
    SFD_SetCond(ply->sfd, 92, b);
    SFD_SetCond(ply->sfd, 91, a);
}

void mwply_SetCond95(MwsfdPly *ply, int a, int b) {
    SFD_SetCond(ply->sfd, 95, b);
    SFD_SetCond(ply->sfd, 95, a);
}

int mwply_SetStmObject(MwsfdPly *ply, int id, void *object, int (*cb)(void *obj, int arg), void *cbObj) {
    return SFD_SetStmObject(ply->sfd, id, object, cb, cbObj);
}

void mwPlySetTimerCh(int ch) {
    if (ch < -1 || ch > 1) {
        mwsfd_Error("E309101 : Timer channel is only -1, 0, 1.");
        return;
    }
    SFD_SetCond(0, SFD_COND_TIMER_CH, ch);
}

int mwPlyGetTimerCh(void) {
    int ch;

    SFD_GetCondDef(0, SFD_COND_TIMER_CH, &ch);
    return ch;
}
