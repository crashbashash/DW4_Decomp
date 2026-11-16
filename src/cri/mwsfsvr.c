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
void SVM_LockSync(void);
void SVM_UnlockSync(void);
void SVM_LockDev(void);
void SVM_UnlockDev(void);
void SVM_LockThrd(void);
void SVM_UnlockThrd(void);
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
int mwPlyExecSvrHndl(MwsfdPly *ply);
void mwsfsfx_SetCompoMode(MwsfdPly *ply);
int MWSFLSC_IsFsStatErr(struct LscObj *lsc);
int LSC_GetNumStm(struct LscObj *lsc);
int mwsst_GetStat(MwsfdSst *sst);
void mwsst_Pause(MwsfdSst *sst, int sw);
void MWSTM_SetFileRange(void *stm, char *fname, void *dir, int ofst, int nsct);
int MWSTM_ReqStart(void *stm);
int MWSTM_GetStat(void *stm);
int MWSTM_IsFsStatErr(void *stm);

/* SFD */
int SFD_GetHnStat(void *sfd);
int SFD_SetConcatPlay(void *sfd);
int SFD_TermSupply(void *sfd);
int SFD_ExecOne(void *sfd);
int SFD_IsHnSvrWait(void *sfd);
int SFD_IsSvrDone(void);
void SFD_VsyncSvr(void);
int SFD_GetSvrStat(void);

extern int mwsfd_init_flag;         /* 1 while MWSFD is initialised */
extern int mwsfsvr_vint_svr_id;
extern int mwsfsvr_vsync_svr_id;
extern int mwsfsvr_mwidle_svr_id;
extern int mwsfsvr_main_svr_id;
extern int mwsfsvr_vsync_cnt;
extern volatile int mwsfsvr_vsync_cnt2;
extern MwsfdPly *mwsfsvr_cur_ply;  /* the player the server is executing */
extern char mwsfd_err_msg[256];

void MWSFSVR_CheckForceSvrBdr(MwsfdPly *ply);
void MWSFD_SetReqSvrBdrHn(MwsfdPly *ply, int sw);
int MWSFSVR_GetHnMwplySvrFlg(MwsfdPly *ply);
int MWSFD_GetReqSvrBdrLib(void);
void MWSFSVR_SetHnMwplySvrFlg(MwsfdPly *ply, int sw);
void MWSFSVR_SetHnSfdSvrFlg(MwsfdPly *ply, int sw);
int mwsfd_ExecSvrHndl(MwsfdPly *ply);
int MWSFSVR_GetMwsfdSvrFlg(void);

void MWSFSVM_Init(void)
{
    SVM_Init();
    mwsfsvr_vint_svr_id = 0;
    mwsfsvr_vsync_svr_id = 0;
    mwsfsvr_mwidle_svr_id = 0;
    mwsfsvr_main_svr_id = 0;
}

void MWSFSVM_Finish(void)
{
    SVM_Finish();
}

void MWSFSVM_EntryVint(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_vint_svr_id = SVM_SetCbSvr(SVM_SVR_VINT, fn, obj);
}

void MWSFSVM_DeleteVint(void)
{
    SVM_DelCbSvr(SVM_SVR_VINT, mwsfsvr_vint_svr_id);
}

void MWSFSVM_EntryVfunc(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_vsync_svr_id = SVM_SetCbSvr(SVM_SVR_VSYNC, fn, obj);
}

void MWSFSVM_EntryIdVfunc(int id, void (*fn)(void *obj), void *obj)
{
    SVM_SetCbSvrId(SVM_SVR_VSYNC, id, fn, obj);
    mwsfsvr_vsync_svr_id = id;
}

void MWSFSVM_DeleteVfunc(void)
{
    SVM_DelCbSvr(SVM_SVR_VSYNC, mwsfsvr_vsync_svr_id);
}

void MWSFSVM_EntryIdleFunc(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_mwidle_svr_id = SVM_SetCbSvr(SVM_SVR_MWIDLE, fn, obj);
}

void MWSFSVM_DeleteIdleFunc(void)
{
    SVM_DelCbSvr(SVM_SVR_MWIDLE, mwsfsvr_mwidle_svr_id);
}

void MWSFSVM_EntryMainFunc(void (*fn)(void *obj), void *obj)
{
    mwsfsvr_main_svr_id = SVM_SetCbSvr(SVM_SVR_MAIN, fn, obj);
}

void MWSFSVM_DeleteMainFunc(void)
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
    SVM_LockSync();
    return 1;
}

void mwsfsvr_UnlockRsc(void)
{
    SVM_UnlockSync();
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

int MWSFSVM_Lock(void)
{
    SVM_LockThrd();
    return 1;
}

void mwsfsvr_UnlockEtc(void)
{
    SVM_UnlockThrd();
}

int MWSFSVM_Unlock(int *flag)
{
    return SVM_TestAndSet(flag);
}

void mwl_callErrCb(const char *msg);

void MWSFSVM_Error(const char *format, ...)
{
    va_list args;

    memset(mwsfd_err_msg, 0, sizeof(mwsfd_err_msg));
    __builtin_stdarg_start(args, format);
    vsprintf(mwsfd_err_msg, format, args);
    mwl_callErrCb(mwsfd_err_msg);
    __builtin_va_end(args);
}

void MWSFSVM_GotoIdleBorder(void)
{
    SVM_GotoSvrBorder(SVM_SVR_MWIDLE);
}

void mwPlyEntryErrFn(void (*fn)(void *obj, const char *msg), void *obj)
{
    ADXM_SetCbErr(fn, obj);
}

void mwl_callErrCb(const char *msg)
{
    SVM_CallErr1(msg);
}

int MWSFSVR_IsEndDec(void)
{
    return SFD_GetSvrStat() != 1;
}

void mwsfsvr_ExecForceSvrBdr(MwsfdPly *ply);

void MWSFSVR_CheckForceSvrBdr(MwsfdPly *ply)
{
    if (ply->svrBusy == 1) {
        mwsfsvr_ExecForceSvrBdr(ply);
    }
}

/* lets the server run for up to 10 frames until it is out of the player */
void mwsfsvr_ExecForceSvrBdr(MwsfdPly *ply)
{
    int i;

    for (i = 0; i < 10; i++) {
        MWSFD_SetReqSvrBdrHn(ply, 1);
        ADXM_ExecVsyncFrame();
        MWSFD_SetReqSvrBdrHn(ply, 0);
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
            if (ply->linkReq == 1 && SFD_SetConcatPlay(ply->sfd) != 0) {
                MWSFSVM_Error(mwply_lnk_err_msg);
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
        if (ply->linkReq == 1 && SFD_SetConcatPlay(ply->sfd) != 0) {
            MWSFSVM_Error(mwply_lnk_err_msg);
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
        MWSFSVM_Error("E211141 MWSTM_ReqStart: can't start '%s'", ply->fname);
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
                MWSFSVM_Error("E99072102 mwlSfdExecDecSvrPlaying: can't term");
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

int mwSfdExecDecSvrHndl(MwsfdPly *ply)
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
    if (lsc != 0 && MWSFLSC_IsFsStatErr(lsc) == 1) {
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
    return (int)mwsflib_GetVersionStr()->prm.decSvr;
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
        execLock = &mwsflib_GetVersionStr()->execLock;
        if (MWSFSVM_Unlock(execLock) != 0) {
            if (mwsfd_init_flag == init) {
                SFD_VsyncSvr();
            }
            *execLock = 0;
        }
    }
}

void mwsfsvr_SetSvrHooks(void (*preFn)(void *obj), void *preObj, void (*postFn)(void *obj), void *postObj)
{
    MwsfdWork *work = mwsflib_GetVersionStr();

    work->preSvrFn = preFn;
    work->preSvrObj = preObj;
    work->postSvrFn = postFn;
    work->postSvrObj = postObj;
}

void mwsfsvr_CallPreSvr(void)
{
    MwsfdWork *work = mwsflib_GetVersionStr();
    void (*fn)(void *obj) = work->preSvrFn;
    void *obj = work->preSvrObj;

    if (fn != 0) {
        fn(obj);
    }
}

void mwsfsvr_CallPostSvr(void)
{
    MwsfdWork *work = mwsflib_GetVersionStr();
    void *obj = work->postSvrObj;
    void (*fn)(void *obj) = work->postSvrFn;

    if (fn != 0) {
        fn(obj);
    }
}

void mwsfsvr_SetIdleHook(void (*fn)(void *obj), void *obj)
{
    MwsfdWork *work = mwsflib_GetVersionStr();

    work->idleFn = fn;
    work->idleObj = obj;
}

void mwsfsvr_CallIdle(void)
{
    MwsfdWork *work = mwsflib_GetVersionStr();
    void *obj = work->idleObj;
    void (*fn)(void *obj) = work->idleFn;

    if (fn != 0) {
        fn(obj);
    }
}

/* one pass of the server: with the server lock taken, runs every player's server step between the
 * pre and post callbacks, then calls the idle callback when SFD has nothing left to do and no
 * caller waits. Returns whether SFD still has work. */
int mwsfsvr_ExecServer(void *obj)
{
    MwsfdWork *work;
    MwsfdPly *ply;
    int i;
    int result;
    int on;

    if (mwsfd_init_flag != 1)
        return 0;
    work = mwsflib_GetVersionStr();
    if (MWSFSVM_Unlock(&work->svrLock) == 0)
        return 0;
    ply = work->ply;
    mwsfsvr_CallPreSvr();
    for (i = 7; i >= 0; i--) {
        if (ply != 0) {
            mwPlyExecSvrHndl(ply);
        }
        ply++;
    }
    MWSFSVR_SetMwsfdSvrFlg(0);
    on = 1; /* matching construct: hand search — the 1 both tests compare with is held in a local, which keeps it in a saved register across the calls */
    result = SFD_IsSvrDone() != on;
    mwsfsvr_CallPostSvr();
    if (result == 0 && MWSFD_GetReqSvrBdrLib() != on)
        mwsfsvr_CallIdle();
    return result;
}

/* matching construct: volatile (unapproved, as before the fold): retail reads used after the NULL
 * test, not in its delay slot */
int mwPlyExecSvrHndl(MwsfdPly *ply)
{
    int used;

    if (mwsfd_init_flag != 1) {
        return 0;
    }
    if (ply == 0) {
        MWSFSVM_Error("E1071901 mwPlyExecSvrHndl: NULL handle.");
        return 0;
    }
    used = *(volatile int *)&ply->used;
    if (used != mwsfd_init_flag) {
        return 0;
    }
    if (MWSFSVR_GetHnMwplySvrFlg(ply) == used) {
        return 0;
    }
    if (MWSFD_GetReqSvrBdrLib() == used) {
        return 0;
    }
    return mwsfd_ExecSvrHndl(ply);
}

/* one server pass over a player; returns non-zero while its SFD has more to do */
int mwsfd_ExecSvrHndl(MwsfdPly *ply)
{
    void *sfd = ply->sfd;
    int used;

    MWSFSVR_SetHnMwplySvrFlg(ply, 1);
    used = ply->used;
    if (used != 1) {
        MWSFSVR_SetHnMwplySvrFlg(ply, 0);
        return 0;
    }
    mwsfsvr_cur_ply = ply;
    MWSFSVR_SetHnSfdSvrFlg(ply, 1);
    SFD_ExecOne(sfd);
    MWSFSVR_SetHnSfdSvrFlg(ply, 0);
    if (ply->stat == 0) {
        ply->execFlg = 0;
    } else {
        ply->execFlg = used;
        mwSfdExecDecSvrHndl(ply);
    }
    MWSFSVR_SetHnMwplySvrFlg(ply, 0);
    return SFD_IsHnSvrWait(sfd) != 1;
}

int MWSFSVR_Vint(void)
{
    mwsfsvr_VsyncProc();
    return 0;
}

void mwsfsvr_Exec(void)
{
    mwsfsvr_ExecServer(0);
}

void MWSFSVR_SetMwsfdSvrFlg(int lock)
{
    mwsflib_GetVersionStr()->svrLock = lock;
}

int MWSFSVR_GetMwsfdSvrFlg(void)
{
    return mwsflib_GetVersionStr()->svrLock;
}

void MWSFSVR_SetHnMwplySvrFlg(MwsfdPly *ply, int sw)
{
    ply->svrBusy = sw;
}

int MWSFSVR_GetHnMwplySvrFlg(MwsfdPly *ply)
{
    return ply->svrBusy;
}

void MWSFSVR_SetHnSfdSvrFlg(MwsfdPly *ply, int sw)
{
    ply->inSfdExec = sw;
}

int MWSFSVR_GetHnSfdSvrFlg(MwsfdPly *ply)
{
    return ply->inSfdExec;
}

int MWSFSVR_IsSvrBdrHndl(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E2011101: MWSFSVR_IsSvrBdrHndl: handle is invalid.");
        return 0;
    }
    return MWSFSVR_GetHnMwplySvrFlg(ply) != 1;
}

void MWSFD_SetReqSvrBdrHn(MwsfdPly *ply, int sw)
{
    MwsfdWork *work = mwsflib_GetVersionStr();

    ply->waitingSvr = sw;
    work->waitingSvr = sw;
}

int MWSFD_GetReqSvrBdrHn(MwsfdPly *ply)
{
    return ply->waitingSvr;
}

int MWSFD_GetReqSvrBdrLib(void)
{
    return mwsflib_GetVersionStr()->waitingSvr;
}

int mwPlyIsSvrBdr(void)
{
    return MWSFSVR_GetMwsfdSvrFlg() != 1;
}

/* runs the idle server up to its border with the player marked waiting, then waits out a pass
 * still in the player */
void mwlSfdSleepDecSvr(MwsfdPly *ply)
{
    mwPlySaveRsc();
    MWSFD_SetReqSvrBdrHn(ply, 1);
    MWSFSVM_GotoIdleBorder();
    MWSFD_SetReqSvrBdrHn(ply, 0);
    mwPlyRestoreRsc();
    MWSFSVR_CheckForceSvrBdr(ply);
}
