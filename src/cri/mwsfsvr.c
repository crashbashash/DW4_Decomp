/* MWSFSVR: the MWSFD server. Registers the player's servers and hooks with SVM, wraps SVM's locks
 * and error report, and runs each player's server step: starting the file read, waiting for the
 * SFD to be prepared, feeding seamless and SST input, and catching stream errors. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/mwsfd.h"
#include "dw4/cri/sfdsj.h"

typedef __builtin_va_list va_list;

void *memset(void *dst, int value, unsigned int size);
int vsprintf(char *buf, const char *format, va_list args);

/* SVM: server manager */
enum {
    SVM_SVR_VINT = 0,
    SVM_SVR_VSYNC = 2,
    SVM_SVR_MAIN = 5,
    SVM_SVR_MWIDLE = 6
};
void SVM_Init(void);
void SVM_Finish(void);
int SVM_SetCbSvr(int svtype, void (*fn)(void *obj), void *obj);
void SVM_SetCbSvrId(int svtype, int id, void (*fn)(void *obj), void *obj);
void SVM_DelCbSvr(int svtype, int id);
void SVM_SetCbVsyncBegin(void (*fn)(void *obj), void *obj);
void SVM_SetCbVsyncEnd(void (*fn)(void *obj), void *obj);
void SVM_LockVar(void);
void SVM_UnlockVar(void);
void SVM_LockRsc(void);
void SVM_UnlockRsc(void);
void SVM_LockDev(void);
void SVM_UnlockDev(void);
void SVM_LockEtc(void);
void SVM_UnlockEtc(void);
int SVM_TestAndSet(int *flag);
void SVM_GotoSvrBorder(int id);
void SVM_CallErr1(const char *msg);
void ADXM_SetCbErr(void (*fn)(void *obj, const char *msg), void *obj);
int ADXM_IsSetupThrd(void);
void ADXM_ExecVsyncFrame(void);

/* the rest of MWSFD */
void mwPlySaveRsc(void);
void mwPlyRestoreRsc(void);
void MWSFSEE_ChkSupply(MwsfdPly *ply);
void MWSFLIB_SetErrCode(int code);
int MWSFD_IsEnableHndl(MwsfdPly *ply);
void MWSFCRE_SetSupplySj(MwsfdPly *ply);
int mwPlySfdStart(MwsfdPly *ply);
void mwSfdPause(MwsfdPly *ply, int sw);
void mwPlyChkSupply(MwsfdPly *ply);
void mwsfsfx_SetCompoMode(MwsfdPly *ply);
int mwsflsc_IsLscErr(struct LscObj *lsc);
int LSC_GetNumStm(struct LscObj *lsc);
int mwsst_GetStat(MwsfdSst *sst);
void mwsst_Pause(MwsfdSst *sst, int sw);
void MWSTM_SetFileRange(void *stm, char *fname, void *dir, int ofst, int nsct);
int MWSTM_ReqStart(void *stm);
int MWSTM_GetStat(void *stm);
int MWSTM_IsFsStatErr(void *stm);

/* SFD */
int SFD_GetHnStat(void *sfd);
int SFD_SetLnkStm(void *sfd);
int SFD_TermSupply(void *sfd);
int SFD_ExecOne(void *sfd);
int SFD_IsHnSvrDone(void *sfd);
int SFD_IsSvrDone(void);
void SFD_VsyncSvr(void);
int SFD_UpdateSysStat(void);

extern int mwsfd_init_flag;         /* 1 while MWSFD is initialised */
extern int mwsfsvr_vint_svr_id;
extern int mwsfsvr_vsync_svr_id;
extern int mwsfsvr_mwidle_svr_id;
extern int mwsfsvr_main_svr_id;
extern int mwsfsvr_vsync_cnt;
extern volatile int mwsfsvr_vsync_cnt2;
extern MwsfdPly *mwsfsvr_cur_ply;  /* the player the server is executing */
extern char mwsfd_err_msg[256];

void mwsfsvr_WaitIfBusy(MwsfdPly *ply);
void mwsfsvr_SetWaitingSvr(MwsfdPly *ply, int sw);
int mwsfsvr_IsSvrBusy(MwsfdPly *ply);
int mwsfsvr_GetWaitingSvr(void);
void mwsfsvr_SetSvrBusy(MwsfdPly *ply, int sw);
void mwsfsvr_SetSfdExecuting(MwsfdPly *ply, int sw);
int mwsfsvr_ExecSvrHndl(MwsfdPly *ply);
int mwsfd_GetSvrLock(void);

void mwsfsvr_Init(void)
{
    SVM_Init();
    mwsfsvr_vint_svr_id = 0;
    mwsfsvr_vsync_svr_id = 0;
    mwsfsvr_mwidle_svr_id = 0;
    mwsfsvr_main_svr_id = 0;
}

void mwsfsvr_Finish(void)
{
    SVM_Finish();
}

void mwsfsvr_SetVintSvr(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_vint_svr_id = SVM_SetCbSvr(SVM_SVR_VINT, fn, obj);
}

void mwsfsvr_DelVintSvr(void)
{
    SVM_DelCbSvr(SVM_SVR_VINT, mwsfsvr_vint_svr_id);
}

void mwsfsvr_SetVsyncSvr(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_vsync_svr_id = SVM_SetCbSvr(SVM_SVR_VSYNC, fn, obj);
}

void mwsfsvr_SetVsyncSvrId(int id, void (*fn)(void *obj), void *obj)
{
    SVM_SetCbSvrId(SVM_SVR_VSYNC, id, fn, obj);
    mwsfsvr_vsync_svr_id = id;
}

void mwsfsvr_DelVsyncSvr(void)
{
    SVM_DelCbSvr(SVM_SVR_VSYNC, mwsfsvr_vsync_svr_id);
}

void mwsfsvr_SetMwIdleSvr(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_mwidle_svr_id = SVM_SetCbSvr(SVM_SVR_MWIDLE, fn, obj);
}

void mwsfsvr_DelMwIdleSvr(void)
{
    SVM_DelCbSvr(SVM_SVR_MWIDLE, mwsfsvr_mwidle_svr_id);
}

void mwsfsvr_SetMainSvr(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_main_svr_id = SVM_SetCbSvr(SVM_SVR_MAIN, fn, obj);
}

void mwsfsvr_DelMainSvr(void)
{
    SVM_DelCbSvr(SVM_SVR_MAIN, mwsfsvr_main_svr_id);
}

void mwsfsvr_VsyncBegin(void *obj);
void mwsfsvr_VsyncEnd(void *obj);

void mwsfsvr_SetVsyncHooks(void)
{
    SVM_SetCbVsyncBegin(mwsfsvr_VsyncBegin, 0);
    SVM_SetCbVsyncEnd(mwsfsvr_VsyncEnd, 0);
}

void mwsfsvr_DelVsyncHooks(void)
{
    SVM_SetCbVsyncBegin(0, 0);
    SVM_SetCbVsyncEnd(0, 0);
}

void mwsfsvr_VsyncBegin(void *obj)
{
    mwPlySaveRsc();
}

void mwsfsvr_VsyncEnd(void *obj)
{
    mwPlyRestoreRsc();
}

int mwsfsvr_LockVar(void)
{
    SVM_LockVar();
    return 1;
}

void mwsfsvr_UnlockVar(void)
{
    SVM_UnlockVar();
}

int mwsfsvr_LockRsc(void)
{
    SVM_LockRsc();
    return 1;
}

void mwsfsvr_UnlockRsc(void)
{
    SVM_UnlockRsc();
}

int mwsfsvr_LockDev(void)
{
    SVM_LockDev();
    return 1;
}

void mwsfsvr_UnlockDev(void)
{
    SVM_UnlockDev();
}

int mwsfsvr_LockEtc(void)
{
    SVM_LockEtc();
    return 1;
}

void mwsfsvr_UnlockEtc(void)
{
    SVM_UnlockEtc();
}

int mwsfsvr_TestAndSet(int *flag)
{
    return SVM_TestAndSet(flag);
}

void mwsfsvr_CallErr1(const char *msg);

void mwsfd_Error(const char *format, ...)
{
    va_list args;

    memset(mwsfd_err_msg, 0, sizeof(mwsfd_err_msg));
    __builtin_stdarg_start(args, format);
    vsprintf(mwsfd_err_msg, format, args);
    mwsfsvr_CallErr1(mwsfd_err_msg);
    __builtin_va_end(args);
}

void MWSFSVM_GotoIdleBorder(void)
{
    SVM_GotoSvrBorder(SVM_SVR_MWIDLE);
}

void mwsfsvr_SetCbErr(void (*fn)(void *obj, const char *msg), void *obj)
{
    ADXM_SetCbErr(fn, obj);
}

void mwsfsvr_CallErr1(const char *msg)
{
    SVM_CallErr1(msg);
}

int mwsfsvr_IsSfdBusy(void)
{
    return SFD_UpdateSysStat() != 1;
}

void mwsfsvr_WaitSvr(MwsfdPly *ply);

void mwsfsvr_WaitIfBusy(MwsfdPly *ply)
{
    if (ply->svrBusy == 1) {
        mwsfsvr_WaitSvr(ply);
    }
}

/* lets the server run for up to 10 frames until it is out of the player */
void mwsfsvr_WaitSvr(MwsfdPly *ply)
{
    int i;

    for (i = 0; i < 10; i++) {
        mwsfsvr_SetWaitingSvr(ply, 1);
        ADXM_ExecVsyncFrame();
        mwsfsvr_SetWaitingSvr(ply, 0);
        if (ply->svrBusy == 0) {
            break;
        }
    }
}

int mwsfsvr_StartStm(MwsfdPly *ply);
void mwply_CheckPrepared(MwsfdPly *ply);
void mwply_ApplyCompoMode(MwsfdPly *ply);

/* starts a pending file read, checks whether preparation has finished, and once SFD plays (its
 * state 4 or 6) marks the player playing and applies the composition mode */
void mwply_UpdateStat(MwsfdPly *ply)
{
    int stmReq = ply->stmReq;
    void *sfd = ply->sfd;
    int st;

    if (stmReq == 1 && mwsfsvr_StartStm(ply) == stmReq) {
        ply->stmReq = 0;
    }
    mwply_CheckPrepared(ply);
    st = SFD_GetHnStat(sfd);
    if (st == 4 || st == 6) {
        ply->stat = 2;
        mwply_ApplyCompoMode(ply);
    }
}

void mwply_ApplyCompoMode(MwsfdPly *ply)
{
    mwsfsfx_SetCompoMode(ply);
}

void mwply_CheckPreparedSst(MwsfdPly *ply);
void mwply_CheckPreparedStm(MwsfdPly *ply);

void mwply_CheckPrepared(MwsfdPly *ply)
{
    if (ply->sst.created == 1) {
        mwply_CheckPreparedSst(ply);
        return;
    }
    mwply_CheckPreparedStm(ply);
}

static const char mwply_lnk_err_msg[] = "E99072103 mwPlyStartXX: can't link stream";

/* SFD prepared (state 3) and the SST input stopped or its SJ empty: starts SFD */
void mwply_CheckPreparedSst(MwsfdPly *ply)
{
    MwsfdSst *sst = &ply->sst;
    int st = SFD_GetHnStat(ply->sfd);
    int sstStat = mwsst_GetStat(sst);

    /* matching construct: manual — nested ifs instead of early returns keep the final call a
     * sibling (tail) call */
    if (st == 3) {
        if (sstStat == 2 || sst->sj->vtbl->getNumData(sst->sj, 1) == 0) {
            mwPlySfdStart(ply);
            if (ply->pause == 0) {
                mwSfdPause(ply, 0);
            }
            if (ply->linkReq == 1 && SFD_SetLnkStm(ply->sfd) != 0) {
                mwsfd_Error(mwply_lnk_err_msg);
            }
            if (ply->pause == 0) {
                mwsst_Pause(sst, 0);
            }
        }
    }
}

void mwply_CheckPreparedStm(MwsfdPly *ply)
{
    if (SFD_GetHnStat(ply->sfd) == 3) {
        mwPlySfdStart(ply);
        if (ply->pause == 0) {
            mwSfdPause(ply, 0);
        }
        if (ply->linkReq == 1 && SFD_SetLnkStm(ply->sfd) != 0) {
            mwsfd_Error(mwply_lnk_err_msg);
        }
    }
}

/* starts the read of the player's file range on its stream; returns 1, or -1 when the stream is
 * in error or will not start */
int mwsfsvr_StartStm(MwsfdPly *ply)
{
    SfdSj *sj;

    if (MWSTM_GetStat(ply->stm) == 2) {
        return -1;
    }
    sj = ply->sj;
    if (sj != 0) {
        sj->vtbl->reset(sj);
    }
    MWSTM_SetFileRange(ply->stm, ply->fname, ply->stmDir, ply->stmOfst, ply->stmNsct);
    if (MWSTM_ReqStart(ply->stm) == -1) {
        ply->stat = 4;
        MWSFLIB_SetErrCode(-102);
        mwsfd_Error("E211141 MWSTM_ReqStart: can't start '%s'", ply->fname);
        ply->stmReq = 0;
        return -1;
    }
    MWSFCRE_SetSupplySj(ply);
    return 1;
}

/* while a link switch-off is pending, waits for the last seamless file and terminates the supply */
void mwlSfdExecDecSvrPlaying(MwsfdPly *ply)
{
    void *sfd = ply->sfd;

    if (ply->linkPrev == 1) {
        if (LSC_GetNumStm(ply->lsc) == 0) {
            if (SFD_TermSupply(sfd) != 0) {
                mwsfd_Error("E99072102 mwlSfdExecDecSvrPlaying: can't term");
            }
            ply->linkPrev = 0;
        }
    } else {
        mwPlyChkSupply(ply);
    }
    if (SFD_GetHnStat(sfd) == 6) {
        ply->stat = 3;
    }
}

void mwsfsvr_CheckStmErr(MwsfdPly *ply);

int mwsfsvr_ExecDecSvr(MwsfdPly *ply)
{
    switch (ply->stat) {
    case 1:
        mwply_UpdateStat(ply);
        break;
    case 2:
        mwlSfdExecDecSvrPlaying(ply);
        break;
    case 0:
    case 3:
    case 4:
    default:
        break;
    }
    mwsfsvr_CheckStmErr(ply);
    MWSFSEE_ChkSupply(ply);
    return 0;
}

/* a stream or seamless-controller error puts the player in state 4 */
void mwsfsvr_CheckStmErr(MwsfdPly *ply)
{
    void *stm = ply->stm;
    struct LscObj *lsc;

    if (stm != 0 && MWSTM_IsFsStatErr(stm) != 0) {
        ply->stat = 4;
    }
    lsc = ply->lsc;
    if (lsc != 0 && mwsflsc_IsLscErr(lsc) == 1) {
        ply->stat = 4;
    }
}

int mwsfsvr_IsDecSvr(void);
int mwsfsvr_ExecVsync(void *obj);
int mwsfsvr_ExecServer(void *obj);

int mwsfsvr_VsyncSvr(void *obj)
{
    int result = 0;

    if (ADXM_IsSetupThrd() == 1) {
        result = mwsfsvr_ExecVsync(obj);
    }
    return result;
}

int mwsfsvr_MainSvr(void *obj)
{
    int result = 0;
    int thrd = ADXM_IsSetupThrd();

    if (thrd == 1) {
        if (mwsfsvr_IsDecSvr() == thrd) {
            result = mwsfsvr_ExecServer(obj);
        }
    } else {
        mwsfsvr_ExecVsync(obj);
        result = mwsfsvr_ExecServer(obj);
    }
    return result;
}

int mwsfsvr_IdleSvr(void *obj)
{
    int result = 0;
    int thrd = ADXM_IsSetupThrd();

    if (thrd == 1 && mwsfsvr_IsDecSvr() != thrd) {
        result = mwsfsvr_ExecServer(obj);
    }
    return result;
}

int mwsfsvr_IsDecSvr(void)
{
    return (int)MWSFLIB_GetLibWorkPtr()->prm.decSvr;
}

void mwsfsvr_VsyncProc(void);

int mwsfsvr_ExecVsync(void *obj)
{
    mwsfsvr_VsyncProc();
    return 0;
}

/* counts the frame and runs the SFD vsync server unless another one holds the execution lock;
 * matching construct: volatile (unapproved, as before the fold) on the second counter */
void mwsfsvr_VsyncProc(void)
{
    int init;
    int *execLock;

    mwsfsvr_vsync_cnt++;
    mwsfsvr_vsync_cnt2++;
    init = mwsfd_init_flag;
    if (init == 1) {
        execLock = &MWSFLIB_GetLibWorkPtr()->execLock;
        if (mwsfsvr_TestAndSet(execLock) != 0) {
            if (mwsfd_init_flag == init) {
                SFD_VsyncSvr();
            }
            *execLock = 0;
        }
    }
}

void mwsfsvr_SetSvrHooks(void (*preFn)(void *obj), void *preObj, void (*postFn)(void *obj), void *postObj)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    work->preSvrFn = preFn;
    work->preSvrObj = preObj;
    work->postSvrFn = postFn;
    work->postSvrObj = postObj;
}

void mwsfsvr_CallPreSvr(void)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();
    void (*fn)(void *obj) = work->preSvrFn;
    void *obj = work->preSvrObj;

    if (fn != 0) {
        fn(obj);
    }
}

void mwsfsvr_CallPostSvr(void)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();
    void *obj = work->postSvrObj;
    void (*fn)(void *obj) = work->postSvrFn;

    if (fn != 0) {
        fn(obj);
    }
}

void mwsfsvr_SetIdleHook(void (*fn)(void *obj), void *obj)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    work->idleFn = fn;
    work->idleObj = obj;
}

void mwsfsvr_CallIdle(void)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();
    void *obj = work->idleObj;
    void (*fn)(void *obj) = work->idleFn;

    if (fn != 0) {
        fn(obj);
    }
}

/* mwsfsvr_ExecServer (0x29ac78) links from the retail image */

/* matching construct: volatile (unapproved, as before the fold): retail reads used after the NULL
 * test, not in its delay slot */
int mwPlyExecSvrHndl(MwsfdPly *ply)
{
    int used;

    if (mwsfd_init_flag != 1) {
        return 0;
    }
    if (ply == 0) {
        mwsfd_Error("E1071901 mwPlyExecSvrHndl: NULL handle.");
        return 0;
    }
    used = *(volatile int *)&ply->used;
    if (used != mwsfd_init_flag) {
        return 0;
    }
    if (mwsfsvr_IsSvrBusy(ply) == used) {
        return 0;
    }
    if (mwsfsvr_GetWaitingSvr() == used) {
        return 0;
    }
    return mwsfsvr_ExecSvrHndl(ply);
}

/* one server pass over a player; returns non-zero while its SFD has more to do */
int mwsfsvr_ExecSvrHndl(MwsfdPly *ply)
{
    void *sfd = ply->sfd;
    int used;

    mwsfsvr_SetSvrBusy(ply, 1);
    used = ply->used;
    if (used != 1) {
        mwsfsvr_SetSvrBusy(ply, 0);
        return 0;
    }
    mwsfsvr_cur_ply = ply;
    mwsfsvr_SetSfdExecuting(ply, 1);
    SFD_ExecOne(sfd);
    mwsfsvr_SetSfdExecuting(ply, 0);
    if (ply->stat == 0) {
        ply->execFlg = 0;
    } else {
        ply->execFlg = used;
        mwsfsvr_ExecDecSvr(ply);
    }
    mwsfsvr_SetSvrBusy(ply, 0);
    return SFD_IsHnSvrDone(sfd) != 1;
}

int mwsfsvr_ExecVsyncSvr(void)
{
    mwsfsvr_VsyncProc();
    return 0;
}

void mwsfsvr_Exec(void)
{
    mwsfsvr_ExecServer(0);
}

void mwsfd_SetSvrLock(int lock)
{
    MWSFLIB_GetLibWorkPtr()->svrLock = lock;
}

int mwsfd_GetSvrLock(void)
{
    return MWSFLIB_GetLibWorkPtr()->svrLock;
}

void mwsfsvr_SetSvrBusy(MwsfdPly *ply, int sw)
{
    ply->svrBusy = sw;
}

int mwsfsvr_IsSvrBusy(MwsfdPly *ply)
{
    return ply->svrBusy;
}

void mwsfsvr_SetSfdExecuting(MwsfdPly *ply, int sw)
{
    ply->inSfdExec = sw;
}

int mwsfsvr_IsSfdExecuting(MwsfdPly *ply)
{
    return ply->inSfdExec;
}

int MWSFSVR_IsSvrBdrHndl(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E2011101: MWSFSVR_IsSvrBdrHndl: handle is invalid.");
        return 0;
    }
    return mwsfsvr_IsSvrBusy(ply) != 1;
}

void mwsfsvr_SetWaitingSvr(MwsfdPly *ply, int sw)
{
    MwsfdWork *work = MWSFLIB_GetLibWorkPtr();

    ply->waitingSvr = sw;
    work->waitingSvr = sw;
}

int mwsfsvr_IsWaitingSvr(MwsfdPly *ply)
{
    return ply->waitingSvr;
}

int mwsfsvr_GetWaitingSvr(void)
{
    return MWSFLIB_GetLibWorkPtr()->waitingSvr;
}

int mwsfsvr_IsSvrUnlocked(void)
{
    return mwsfd_GetSvrLock() != 1;
}

/* runs the idle server up to its border with the player marked waiting, then waits out a pass
 * still in the player */
void mwlSfdSleepDecSvr(MwsfdPly *ply)
{
    mwPlySaveRsc();
    mwsfsvr_SetWaitingSvr(ply, 1);
    MWSFSVM_GotoIdleBorder();
    mwsfsvr_SetWaitingSvr(ply, 0);
    mwPlyRestoreRsc();
    mwsfsvr_WaitIfBusy(ply);
}
