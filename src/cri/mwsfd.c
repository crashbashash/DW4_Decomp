/* MWSFD: the Sofdec player library's core (MWSFD/PS2EE Ver.3.33s281). The version string, the work
 * area and its settings, the library init and finish over SFD and the SFD time hooks. */
#include "dw4/cri/mwsfd.h"

/* the parameter block of the SFD library init */
typedef struct SfdInitPrm {
    int f0;
    int arg;    /* 4 */
} SfdInitPrm;

#define SFD_VERSION_WORK 14072

extern char mwsfd_version[];        /* "\nMWSFD/PS2EE Ver.3.33s281 Build:..." */
extern MwsfdWork mwsfd_work;
extern int mwsfd_init_cnt;           /* init reference count */
extern int mwsfd_err_mwsfdhn;
extern SfdInitPrm mwsfd_sfd_iprm;     /* the default SFD init parameters */
extern char mwsfd_sfd_version[];    /* "1.946", the SFD version this build needs */
extern char E011081_mwPlySfdInit_Not_compatible_SFD_Version[];

void *memset(void *dst, int c, unsigned int n);
void mwsfd_Error(const char *message, ...);
void mwsfd_SetSvrLock(int value);
void LSC_Finish(void);
void ADXT_Finish(void);
void SJMEM_Finish(void);
void SJRBF_Finish(void);
void SJUNI_Finish(void);
void mwsfcre_DestroyPly(MwsfdPly *ply);
void MWSFD_FinishRsc(void);
void *mwPlyGetSfdHn(MwsfdPly *ply);
void MWSFD_SetCond(MwsfdPly *ply, int id, int value);
void mwsfsfx_Finish(void);
void mwsfsvr_Finish(void);
void mwsfsvr_SetVsyncSvrId(int n, void (*fn)(), int arg);
void mwsfsvr_DelVsyncSvr(void);
void mwsfsvr_SetMwIdleSvr(void (*fn)(), int arg);
void mwsfsvr_DelMwIdleSvr(void);
void mwsfsvr_SetMainSvr(void (*fn)(), int arg);
void mwsfsvr_DelMainSvr(void);
void mwsfsvr_SetVsyncHooks(void);
void mwsfsvr_DelVsyncHooks(void);
void mwsfsvr_VsyncSvr();
void mwsfsvr_MainSvr();
void mwsfsvr_IdleSvr();
void MWSTM_FinishStatic(void);
int SFD_IsHnSize(const char *version, int size);
int SFD_Init(SfdInitPrm *prm);
void SFD_Finish(void);
int SFD_SetErrFn(int a, void (*fn)(), int b);
void SFD_SetExtClockFn(void *sfd, int a, int b, int c);
void SFD_UpdateTime(void *sfd);

void mwPlyInitSfdFx(void);
void MWSFLIB_SfdErrFunc();
int MWSFD_GetPauseBdr(void);
int MWSFLIB_SetErrCode(int code);
int mwPlySfdFinish(void);


char *MWSFD_GetVersionStr(void)
{
    return mwsfd_version;
}

MwsfdWork *MWSFLIB_GetLibWorkPtr(void)
{
    return &mwsfd_work;
}

/* the SFD error callback: reports the message, ignoring the context */
void mwsflib_LscErrFunc(void *obj, const char *msg)
{
    mwsfd_Error(msg);
}

void mwsflib_SetSvrFunc(void)
{
    mwsfsvr_SetVsyncSvrId(2, mwsfsvr_VsyncSvr, 0);
    mwsfsvr_SetMainSvr(mwsfsvr_MainSvr, 0);
    mwsfsvr_SetMwIdleSvr(mwsfsvr_IdleSvr, 0);
    mwsfsvr_SetVsyncHooks();
}

/* clears the work area and takes the init parameters, or the defaults (59.94 Hz, display cycle 1,
 * latency 1, no decode server) without them */
void mwsflib_InitLibWork(MwsfdInitPrm *iprm)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();
    MwsfdInitPrm *prm;

    memset(work, 0, sizeof(MwsfdWork));
    mwsfd_SetSvrLock(0);
    work->execLock = 0;
    prm = &work->prm;
    if (iprm != 0) {
        prm->vhz = iprm->vhz;
        prm->dispCycle = iprm->dispCycle;
        prm->dispLatency = iprm->dispLatency;
        prm->decSvr = iprm->decSvr;
    } else {
        prm->vhz = 59.94f;
        prm->dispCycle = 1;
        prm->dispLatency = 1;
        prm->decSvr = 0;
    }
    work->picUsrEnable = 1;
    work->waitSvrOnStart = 1;
}

void MWSFD_SetUsePicUsr(int enable)
{
    MWSFLIB_GetLibWorkPtr()->picUsrEnable = enable;
}

int MWSFD_GetUsePicUsr(void)
{
    return MWSFLIB_GetLibWorkPtr()->picUsrEnable;
}

void MWSFD_SetPauseBdr(int wait)
{
    MWSFLIB_GetLibWorkPtr()->waitSvrOnStart = wait;
}

int MWSFD_GetPauseBdr(void)
{
    return MWSFLIB_GetLibWorkPtr()->waitSvrOnStart;
}

void mwsflib_SetDefCond(MwsfdInitPrm *prm)
{
    MWSFD_SetCond(0, 27, (int)prm->vhz);
    MWSFD_SetCond(0, 7, 1);
}

void mwPlyResetSfdFx(void)
{
    if (mwsfd_init_cnt != 0) {
        mwsfd_init_cnt = 0;
        mwPlyInitSfdFx();
    }
}

/* drops the init count; at zero, finishes every player in use and shuts the libraries down */
void mwPlyFinishSfdFx(void)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();
    MwsfdPly *ply;
    int i;

    if (--mwsfd_init_cnt != 0) {
        return;
    }
    ply = work->ply;
    for (i = 0; i < MWSFD_NPLY; i++) {
        if (ply->used == 1) {
            mwsfcre_DestroyPly(ply);
        }
        ply++;
    }
    mwsfsvr_DelVsyncHooks();
    mwsfsvr_DelVsyncSvr();
    mwsfsvr_DelMainSvr();
    mwsfsvr_DelMwIdleSvr();
    mwsfsfx_Finish();
    LSC_Finish();
    mwPlySfdFinish();
    ADXT_Finish();
    MWSTM_FinishStatic();
    SJUNI_Finish();
    SJMEM_Finish();
    SJRBF_Finish();
    MWSFD_FinishRsc();
    mwsfsvr_Finish();
}

int MWSFLIB_SetErrCode(int code)
{
    MWSFLIB_GetLibWorkPtr()->errCode = code;
    return code;
}

int MWSFD_GetErrCode(void)
{
    return MWSFLIB_GetLibWorkPtr()->errCode;
}

/* checks the SFD library version, initialises it and installs the error callback */
int mwPlySfdInit(int arg)
{
    SfdInitPrm prm = mwsfd_sfd_iprm;
    int result;

    prm.arg = arg;
    if (SFD_IsHnSize(mwsfd_sfd_version, SFD_VERSION_WORK) != 1) {
        mwsfd_Error(E011081_mwPlySfdInit_Not_compatible_SFD_Version);
        return -1;
    }
    if (SFD_Init(&prm) != 0) {
        return MWSFLIB_SetErrCode(-301);
    }
    result = SFD_SetErrFn(0, MWSFLIB_SfdErrFunc, 0);
    if (result != 0) {
        result = MWSFLIB_SetErrCode(-303);
    }
    return result;
}

int mwPlySfdFinish(void)
{
    SFD_Finish();
    return 0;
}

int mwsfd_GetMode(void)
{
    return mwsfd_err_mwsfdhn;
}

void MWSFLIB_SetSeekFlg(int flag)
{
    MWSFLIB_GetLibWorkPtr()->workFlag = flag;
}

int MWSFLIB_GetSeekFlg(void)
{
    return MWSFLIB_GetLibWorkPtr()->workFlag;
}

void mwply_SetTimeFn(MwsfdPly *ply, int a, int b, int c)
{
    SFD_SetExtClockFn(mwPlyGetSfdHn(ply), a, b, c);
}

void mwply_ExecTime(MwsfdPly *ply)
{
    if (ply != 0) {
        SFD_UpdateTime(mwPlyGetSfdHn(ply));
        return;
    }
    SFD_UpdateTime(0);
}

