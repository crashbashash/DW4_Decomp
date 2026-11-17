/* MWSFD: the Sofdec player library's core (MWSFD/PS2EE Ver.3.33s281). The version string, the work
 * area and its settings, the library init and finish over SFD and the SFD time hooks. */
#include "dw4/cri/cri_mwsfd.h"
#include <stdio.h>
#include <string.h>
#include "dw4/cri/sfd.h"
#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/lsc.h"
#include "dw4/cri/sj.h"

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
extern int mwsfd_err_sfdhn;
extern SfdInitPrm mwsfd_sfd_iprm;     /* the default SFD init parameters */
extern char mwsfd_sfd_version[];    /* "1.946", the SFD version this build needs */
extern char E011081_mwPlySfdInit_Not_compatible_SFD_Version[];
extern char E1122611_mwPlyInitSfdFx_iprm_is_NULL[];         /* "E1122611 mwPlyInitSfdFx: iprm is NULL." */
extern char E2005_mwPlyInitSfdFx_cant_init_GSC[];           /* "E2005 mwPlyInitSfdFx: can't init GSC" */
extern char ERR20010421A_mwPlyInitSfdFx[];                  /* "ERR20010421A : mwPlyInitSfdFx" */
extern char mwsfd_errfmt_data[];       /* "DATA ERROR(%08X)" */
extern char mwsfd_errfmt_dec[];        /* "DEC ERROR(%08X): " */
extern char mwsfd_errfmt_max_size[];   /* "SFD ERROR(%08X): 'max_width, max_height' of creation parameter is small. ..." */
extern char mwsfd_errfmt_read_buf[];   /* "SFD ERROR(%08X): Read buffer is small. ..." */
extern char mwsfd_errfmt_frm_pool[];   /* "SFD ERROR(%08X): Frame pool size is incorrect. ..." */
extern char mwsfd_errfmt_adxt_num[];   /* "SFD ERROR(%08X): Number of ADXT handles exceeds its maximum number. ..." */
extern char mwsfd_errfmt_other[];      /* "SFD ERROR(%08X)" */
extern char *volatile mwsfd_version_ptr;        /* set to mwsfd_version when the library is initialised */
extern int mwsfd_err_hist[16];         /* the error codes SFD reported, in order (the last slot stays free) */
extern int mwsfd_err_hist_cnt;
extern char mwsfd_err_text[];          /* the formatted SFD error report */
/* kept here: the approved volatile (the vsync server writes it); declared in a header it would apply to every includer */
extern volatile int mwsfsvr_vsync_cnt2; /* bumped by the vsync server */

void LSC_EntryErrFunc(void (*fn)(void *obj, const char *msg), void *obj);
int mwPlySfdInit(int arg);
void MWSFSVM_EntryIdVfunc(int n, void (*fn)(), int arg);
void MWSFSVM_EntryIdleFunc(void (*fn)(), int arg);
void MWSFSVM_EntryMainFunc(void (*fn)(), int arg);
int SFD_SetErrFn(int a, void (*fn)(), int b);

void mwsflib_LscErrFunc(void *obj, const char *msg);
void mwsflib_SetSvrFunc(MwsfdInitPrm *iprm);
void mwsflib_InitLibWork(MwsfdInitPrm *iprm);
void mwsflib_SetDefCond(MwsfdInitPrm *prm);
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
    MWSFSVM_Error(msg);
}

/* starts the library on the first call: the server, the resource and SFD layers and the error
 * hooks, with the display latency lowered by two frames; later calls only count */
void mwPlyInitSfdFx(MwsfdInitPrm *iprm)
{
    MwsfdInitPrm prm;

    if (iprm == 0) {
        MWSFSVM_Error(E1122611_mwPlyInitSfdFx_iprm_is_NULL);
        return;
    }
    memset(&prm, 0, sizeof(MwsfdInitPrm));
    prm.vhz = iprm->vhz;
    prm.dispCycle = iprm->dispCycle;
    prm.dispLatency = iprm->dispLatency;
    prm.decSvr = iprm->decSvr;
    prm.reserved16[0] = iprm->reserved16[0];
    prm.reserved16[1] = iprm->reserved16[1];
    prm.reserved16[2] = iprm->reserved16[2];
    prm.reserved16[3] = iprm->reserved16[3];
    mwsfd_version_ptr = mwsfd_version;
    MWSFSVM_Init();
    MWSFD_InitRsc();
    prm.dispLatency -= 2;
    if (prm.dispLatency < 0) {
        prm.dispLatency = 0;
    }
    if (mwsfd_init_cnt == 0) {
        ADXT_Init();
        SJRBF_Init();
        SJMEM_Init();
        SJUNI_Init();
        if (MWSTM_InitStatic() != 0) {
            MWSFLIB_SetErrCode(-101);
            MWSFSVM_Error(E2005_mwPlyInitSfdFx_cant_init_GSC);
        }
        mwsflib_InitLibWork(&prm);
        mwsfsvr_vsync_cnt2 = 0;
        if (mwPlySfdInit((int)(prm.vhz * 1000.0f + 0.5f)) != 0) {
            MWSFSVM_Error(ERR20010421A_mwPlyInitSfdFx);
        }
        mwsfd_init_flag = 1;
        mwsflib_SetDefCond(&prm);
        LSC_Init();
        LSC_EntryErrFunc(mwsflib_LscErrFunc, 0);
        MWSFSFX_Init();
        mwsflib_SetSvrFunc(&prm);
    }
    mwsfd_init_cnt++;
}

void mwsflib_SetSvrFunc(MwsfdInitPrm *iprm)
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
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();
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

void mwPlyResetSfdFx(MwsfdInitPrm *iprm)
{
    if (mwsfd_init_cnt != 0) {
        mwsfd_init_cnt = 0;
        mwPlyInitSfdFx(iprm);
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

/* the SFD error callback: keeps the player and SFD handles it was raised for and the code in the history,
 * then reports the code with the text for it */

int MWSFD_GetErrMwplyHn(void)
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
