/* CRI MWSFD: the Sofdec player (MWPLY) on top of SFD; the work area with the library's settings, the
 * server hooks and the 8 player handles, and the player functions. */
#ifndef DW4_CRI_CRI_MWSFD_H
#define DW4_CRI_CRI_MWSFD_H

#include "dw4/cri/mwply.h"

struct MwsfdFrm;

#define MWSFD_NPLY 8

/* the init parameters of mwPlyInitSfdFx, which copies all 32 bytes into the work area */
typedef struct MwsfdInitPrm {
    float vhz;          /* 0 */
    int dispCycle;      /* 4 */
    int dispLatency;    /* 8 */
    void *decSvr;       /* 12: the decode server; 1 runs it in a thread (typed apart from the ints: mwsflib_InitLibWork matches only so) */
    int reserved16[4];  /* 16 */
} MwsfdInitPrm;

typedef struct MwsfdWork {
    int f0;
    MwsfdInitPrm prm;              /* 4 */
    int waitingSvr;                /* 36 */
    void *(*mallocFn)(void *obj, int size);  /* 40: mwPlySetMallocFn */
    void (*freeFn)(void *obj, void *ptr);    /* 44 */
    void *mallocObj;                         /* 48 */
    int workFlag;                  /* 52 */
    int picUsrEnable;              /* 56: picture user data is handled */
    int waitSvrOnStart;            /* 60 */
    void (*preSvrFn)(void *obj);   /* 64: called before the server's player loop */
    void *preSvrObj;               /* 68 */
    void (*postSvrFn)(void *obj);  /* 72: called after it */
    void *postSvrObj;              /* 76 */
    void (*idleFn)(void *obj);     /* 80: called when no player is pending */
    void *idleObj;                 /* 84 */
    int svrLock;                   /* 88 */
    int execLock;                  /* 92 */
    char pad96[8];
    int errCode;                   /* 104: the last error code, MWSFLIB_SetErrCode */
    MwsfdPly ply[MWSFD_NPLY];      /* 108 */
} MwsfdWork;


/* The three planes of a YCC frame: their addresses and strides. */
typedef struct MwsfdPlanes {
    char *addr0;
    char *addr1;
    char *addr2;
    int stride0;
    int stride1;
    int stride2;
} MwsfdPlanes;

struct AdxStmObj;
struct LscObj;

#ifdef __cplusplus
extern "C" {
#endif

MwsfdWork *MWSFLIB_GetLibWorkPtr(void);
void MWSFSVR_SetMwsfdSvrFlg(int lock);

/* player parameters */
void *mwPlyGetSfdHn(MwsfdPly *ply);
void mwPlySetAudioCh(MwsfdPly *ply, int ch);
void MWSFD_SetCond(MwsfdPly *ply, int param, int value);
void MWSFD_SetFlowLimit(MwsfdPly *ply, int limit, int cap);
int MWSFD_IsEnableHndl(MwsfdPly *ply);
SfdSj *mwPlyGetInputSj(MwsfdPly *ply);
void mwPlySetTimerCh(int ch);

/* player creation */
int mwPlyCalcWorkCprmSfd(MwsfdCreInf *cprm);
MwsfdPly *mwPlyCreateSofdec(MwsfdCreInf *cprm);
void MWSFCRE_SetSupplySj(MwsfdPly *ply);
int MWSFCRE_ResetSfdHn(MwsfdPly *ply);
void mwSfdDestroy(MwsfdPly *ply);
void mwPlyGetHdrInf(char *buf, int size, MwsfdHdrInf *out);

/* the library */
void mwPlyInitSfdFx(MwsfdInitPrm *iprm);
int MWSFD_GetUsePicUsr(void);
int MWSFD_GetPauseBdr(void);
void mwPlyFinishSfdFx(void);
int MWSFLIB_SetErrCode(int code);
void MWSFLIB_SfdErrFunc(MwsfdPly *ply, int code);
void mwPlyGetCurFrm(MwsfdPly *ply, struct MwsfdFrm *out);

/* 1 while MWSFD is initialised */
extern int mwsfd_init_flag;


/* resources and the scratchpad */
void MWSFD_InitRsc(void);
void MWSFD_FinishRsc(void);
void MWSFD_ExecSetSprCbFn(void *ply);
void MWSFD_ExecVsyncFrame(void);
void mwPlySaveRsc(void);
void mwPlyRestoreRsc(void);
void MWSFSEE_StartFnameSub1(void *ply, int ofst, int nsct);
void MWSFSEE_StartFnameSub2(void *ply, int ofst, int nsct);
void MWSFSEE_ChkSupply(void *ply);

/* frames */
void mwPlyCalcYccPlane(int a, int b, int c, MwsfdPlanes *out);
void mwPlyRelCurFrm(MwsfdPly *ply);
int mwPlyGetNumSkipDisp(MwsfdPly *ply);
void mwply_GetPicInf(char *buf, unsigned int size, MwsfdHdrInf *hdr);
int mwPlyGetCurPicCompoMode(MwsfdPly *ply);
void mwply_ResetPicLog(MwsfdPly *ply);
void mwply_SetPicUsrCb(MwsfdPly *ply);

/* loop playback through LSC */
void mwPlyStartFnameLp(MwsfdPly *ply, const char *fname);
void mwPlyStartAfsLp(MwsfdPly *ply, int patid, int fid);
int MWSFLSC_IsFsStatErr(struct LscObj *lsc);
void MWSFLSC_SetFlowLimit(MwsfdPly *ply, int min);
void mwPlyLinkStm(void *hn, int sw);

/* playback */
int mwPlySfdStart(MwsfdPly *ply);
int mwPlyIsPause(MwsfdPly *ply);
void mwSfdStartSj(MwsfdPly *ply, SfdSj *sj);
void mwSfdStopDec(MwsfdPly *ply);
void mwSfdPause(MwsfdPly *ply, int sw);
void mwPlyStartAfs(MwsfdPly *ply, int dir, int ofst);
void MWSFPLY_SetFlowLimit(MwsfdPly *ply);
void mwPlyChkSupply(MwsfdPly *ply);
void MWSFPLY_RecordFname(MwsfdPly *ply, const char *fname);

/* audio output */
void MWSFRNA_SetOutVol(MwsfdPly *ply, int vol);
int MWSFRNA_GetOutVol(MwsfdPly *ply);
void MWSFRNA_SetOutPan(MwsfdPly *ply, int ch, int pan);
int MWSFRNA_GetOutPan(MwsfdPly *ply, int ch);

/* frame effects and tags */
void MWSFSFX_Init(void);
void MWSFSFX_Finish(void);
int MWSFSFX_CalcHnWorkSiz(int width, int height);
void MWSFSFX_Destroy(void *sfx);
void MWSFSFX_SetCompoMode(MwsfdPly *ply, int mode);
void MWSFSFX_SetFxType(MwsfdPly *ply, int value);
void MWSFSFX_SetColAdj(MwsfdPly *ply, int value);
void MWSFD_SetColAdj(MwsfdPly *ply, int value);
int MWSFTAG_IsUseAinfSj(MwsfdCreInf *cre);
void MWSFTAG_DestroyAinfSj(MwsfdPly *ply);
int MWSFTAG_SetAinfSj(MwsfdPly *ply);
void mwsfsfx_ResetAddInf(MwsfdPly *ply);
void MWSFTAG_ResetAinfSj(MwsfdPly *ply);
void mwsfsfx_UpdateAddInf(MwsfdPly *ply);
void MWSFSFX_SetPicUsrDat(MwsfdPly *ply, char *ud, int size);
int MWSFSFX_IsFrmCcs(MwsfdPly *ply);
int MWSFD_IsFrmDivField(MwsfdPly *ply);
void mwsfsfx_SetCompoMode(MwsfdPly *ply);

/* the stream starter */
void mwsst_Start(MwsfdSst *sst);
void mwsst_Stop(MwsfdSst *sst);
int mwsst_GetStat(MwsfdSst *sst);
void mwsst_Pause(MwsfdSst *sst, int sw);
void MWSST_Restart(MwsfdPly *ply);
void MWSST_Destroy(MwsfdSst *sst);

/* the servers */
void MWSFSVM_Init(void);
void MWSFSVM_Finish(void);
void MWSFSVM_DeleteVfunc(void);
void MWSFSVM_DeleteIdleFunc(void);
void MWSFSVM_DeleteMainFunc(void);
void mwsfsvr_SetVsyncHooks(void);
void mwsfsvr_DelVsyncHooks(void);
void MWSFSVM_Error(const char *format, ...);
void MWSFSVM_GotoIdleBorder(void);
int mwsfsvr_VsyncSvr(void *obj);
int mwsfsvr_MainSvr(void *obj);
int mwsfsvr_IdleSvr(void *obj);
void MWSFSVR_SetHnMwplySvrFlg(MwsfdPly *ply, int sw);
void MWSFSVR_SetHnSfdSvrFlg(MwsfdPly *ply, int sw);
void mwlSfdSleepDecSvr(MwsfdPly *ply);

/* MWSTM: the file stream */
int MWSTM_InitStatic(void);
int MWSTM_FinishStatic(void);
int MWSTM_SetRdSct(struct AdxStmObj *stm, int nsct);
int MWSTM_SetTrSct(struct AdxStmObj *stm);
int MWSTM_IsFsStatErr(struct AdxStmObj *stm);
void MWSTM_SetFlowLimit(struct AdxStmObj *stm, int min, int max);
void MWSTM_GetFlowLimit(struct AdxStmObj *stm, int *min, int *max);
void MWSTM_GetFsizeByte(struct AdxStmObj *stm, int *len);
int MWSTM_GetStatRead(struct AdxStmObj *stm);
struct AdxStmObj *MWSTM_Create(SfdSj *sj);
void MWSTM_Destroy(struct AdxStmObj *stm);
void MWSTM_SetFileRange(struct AdxStmObj *stm, char *fname, void *dir, int ofst, int nsct);
int MWSTM_ReqStart(struct AdxStmObj *stm);
void MWSTM_ReqStop(struct AdxStmObj *stm);
int MWSTM_GetStat(struct AdxStmObj *stm);

#ifdef __cplusplus
}
#endif

#endif
