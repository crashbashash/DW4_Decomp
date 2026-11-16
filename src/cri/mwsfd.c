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
void MWSFSVM_Error(const char *message, ...);
void MWSFSVR_SetMwsfdSvrFlg(int value);
void LSC_Finish(void);
void ADXT_Finish(void);
void SJMEM_Finish(void);
void SJRBF_Finish(void);
void SJUNI_Finish(void);
void mwSfdDestroy(MwsfdPly *ply);
void MWSFD_FinishRsc(void);
void *mwPlyGetSfdHn(MwsfdPly *ply);
void MWSFD_SetCond(MwsfdPly *ply, int id, int value);
void MWSFSFX_Finish(void);
void MWSFSVM_Finish(void);
void MWSFSVM_EntryIdVfunc(int n, void (*fn)(), int arg);
void MWSFSVM_DeleteVfunc(void);
void MWSFSVM_EntryIdleFunc(void (*fn)(), int arg);
void MWSFSVM_DeleteIdleFunc(void);
void MWSFSVM_EntryMainFunc(void (*fn)(), int arg);
void MWSFSVM_DeleteMainFunc(void);
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

MwsfdWork *mwsflib_GetVersionStr(void)
{
    return &mwsfd_work;
}

/* the SFD error callback: reports the message, ignoring the context */
void mwsflib_LscErrFunc(void *obj, const char *msg)
{
    MWSFSVM_Error(msg);
}

void mwsflib_SetSvrFunc(void)
{
    MWSFSVM_EntryIdVfunc(2, mwsfsvr_VsyncSvr, 0);
    MWSFSVM_EntryMainFunc(mwsfsvr_MainSvr, 0);
    MWSFSVM_EntryIdleFunc(mwsfsvr_IdleSvr, 0);
    mwsfsvr_SetVsyncHooks();
}

/* clears the work area and takes the init parameters, or the defaults (59.94 Hz, display cycle 1,
 * latency 1, no decode server) without them */
void mwsflib_InitLibWork(MwsfdInitPrm *iprm)
{
    MwsfdWork *work = mwsflib_GetVersionStr();
    MwsfdInitPrm *prm;

    memset(work, 0, sizeof(MwsfdWork));
    MWSFSVR_SetMwsfdSvrFlg(0);
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
    mwsflib_GetVersionStr()->picUsrEnable = enable;
}

int MWSFD_GetUsePicUsr(void)
{
    return mwsflib_GetVersionStr()->picUsrEnable;
}

void MWSFD_SetPauseBdr(int wait)
{
    mwsflib_GetVersionStr()->waitSvrOnStart = wait;
}

int MWSFD_GetPauseBdr(void)
{
    return mwsflib_GetVersionStr()->waitSvrOnStart;
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
    MwsfdWork *work = mwsflib_GetVersionStr();
    MwsfdPly *ply;
    int i;

    if (--mwsfd_init_cnt != 0) {
        return;
    }
    ply = work->ply;
    for (i = 0; i < MWSFD_NPLY; i++) {
        if (ply->used == 1) {
            mwSfdDestroy(ply);
        }
        ply++;
    }
    mwsfsvr_DelVsyncHooks();
    MWSFSVM_DeleteVfunc();
    MWSFSVM_DeleteMainFunc();
    MWSFSVM_DeleteIdleFunc();
    MWSFSFX_Finish();
    LSC_Finish();
    mwPlySfdFinish();
    ADXT_Finish();
    MWSTM_FinishStatic();
    SJUNI_Finish();
    SJMEM_Finish();
    SJRBF_Finish();
    MWSFD_FinishRsc();
    MWSFSVM_Finish();
}

int MWSFLIB_SetErrCode(int code)
{
    mwsflib_GetVersionStr()->errCode = code;
    return code;
}

int MWSFD_GetErrCode(void)
{
    return mwsflib_GetVersionStr()->errCode;
}

/* checks the SFD library version, initialises it and installs the error callback */
int mwPlySfdInit(int arg)
{
    SfdInitPrm prm = mwsfd_sfd_iprm;
    int result;

    prm.arg = arg;
    if (SFD_IsHnSize(mwsfd_sfd_version, SFD_VERSION_WORK) != 1) {
        MWSFSVM_Error(E011081_mwPlySfdInit_Not_compatible_SFD_Version);
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

int MWSFD_GetErrMwplyHn(void)
{
    return mwsfd_err_mwsfdhn;
}

void MWSFLIB_SetSeekFlg(int flag)
{
    mwsflib_GetVersionStr()->workFlag = flag;
}

int MWSFLIB_GetSeekFlg(void)
{
    return mwsflib_GetVersionStr()->workFlag;
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

