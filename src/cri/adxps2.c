#include "dw4/eekernel.h"

typedef struct AdxmCallback {
    void (*func)(void *arg);
    void *arg;
} AdxmCallback;

/* Thread priorities and the two user-thread stacks, as ADXM_SetupThrdEx takes them. */
typedef struct AdxmThreadPrmEx {
    int lockPrio;
    int safePrio;
    int usrVsyncPrio;
    int vsyncPrio;
    int fsPrio;
    int mainPrio;
    int mwIdlePrio;
    int usrIdlePrio;
    void *usrVsyncStack;
    int usrVsyncStackSize;
    void *usrIdleStack;
    int usrIdleStackSize;
} AdxmThreadPrmEx;

/* The priorities ADXM_SetupThrd takes. */
typedef struct AdxmThreadPrm {
    int lockPrio;
    int safePrio;
    int vsyncPrio;
    int fsPrio;
    int mainPrio;
    int mwIdlePrio;
} AdxmThreadPrm;

/* The priorities ADXPS2_SetupThrd takes; the FS and MW-idle ones are derived from them. */
typedef struct Adxps2ThreadPrm {
    int lockPrio;
    int safePrio;
    int vsyncPrio;
    int mainPrio;
} Adxps2ThreadPrm;

#define ADXPS2_MWIDLE_PRIO 25

extern int adxm_usridle_mode;
extern int adxm_setup_count;
extern AdxmThreadPrmEx adxm_tprm;
extern int adxm_lock_level;
extern volatile int adxm_border_request;
extern volatile int adxm_vsync_busy;
extern volatile int adxm_fs_busy;
extern volatile int adxm_mwidle_busy;
extern volatile int adxm_usridle_busy;
extern volatile int adxm_usrvsync_busy;
extern volatile int adxm_vsync_waiting;
extern volatile long long adxm_usrvsync_count;
extern long long adxm_safe_loop_count;
extern volatile long long adxm_vsync_count;
extern volatile long long adxm_fs_count;
extern volatile long long adxm_mwidle_count;
extern volatile long long adxm_usridle_count;
extern volatile int adxm_safe_thid;
extern volatile int adxm_usrvsync_thid;
extern volatile int adxm_vsync_thid;
extern volatile int adxm_fs_thid;
extern volatile int adxm_main_thid;
extern volatile int adxm_mwidle_thid;
extern volatile int adxm_usridle_thid;
extern volatile long long adxm_safe_exit_request;
extern volatile long long adxm_safe_exited;
extern volatile long long adxm_usrvsync_exit_request;
extern volatile long long adxm_usrvsync_exited;
extern volatile long long adxm_vsync_exit_request;
extern volatile long long adxm_vsync_exited;
extern volatile long long adxm_fs_exit_request;
extern volatile long long adxm_fs_exited;
extern volatile long long adxm_mwidle_exit_request;
extern volatile long long adxm_mwidle_exited;
extern volatile long long adxm_usridle_exit_request;
extern volatile long long adxm_usridle_exited;
extern int adxps2_server_busy;
extern unsigned short adxm_fs_bgcolor;
extern volatile int adxm_mwidle_slept;
extern char adxm_safe_stack[];
extern char adxm_usrvsync_stack[];
extern char adxm_vsync_stack[];
extern char adxm_fs_stack[];
extern char adxm_mwidle_stack[];
extern char adxm_usridle_stack[];
extern int adxm_lock_saved_prio;
extern int adxm_lock_thid;
extern int adxm_main_init_prio;
extern char text_1060102_Internal_Error_adxm_goto[];
extern char ADXM_UsrVsyncThread_Stack_pointe[];
extern char ADXM_UsrIdleThread_Stack_pointer[];
extern char _gp[];
extern AdxmCallback adxm_vsync_frame_cb;
extern AdxmCallback adxm_mwidle_sleep_cb;

int SVM_SetCbLock();
void SVM_SetCbUnlock(int a, int b);
int SVM_Finish();
void SVM_CallErr1(const char *message);
int SVM_Lock();
int SVM_Unlock();
int SVM_SetCbSvrId();
int SVM_GotoSvrBorder();
int SVM_SetCbErr();
int SVM_ExecSvrUsrVsync();
int SVM_ExecSvrVsync();
int SVM_ExecSvrFs();
int SVM_ExecSvrMain();
int SVM_ExecSvrMwIdle();
int SVM_ExecSvrUsrIdle();
int SVM_ExecVsyncBegin();
int SVM_ExecVsyncEnd();
int ADXT_ExecServer();
int ADXT_ExecFsSvr();
void ADXMSG_PrintErr(const char *format, ...);

void adxm_wakeup_thrd(int threadId);
int adxm_resume_thrd(int threadId);
int adxm_suspend_thrd(int threadId);
void adxm_sleep_thrd(void);
int adxm_is_usridle_mode(void);
void adxm_call_mwidle_sleep_cb(void);
void adxm_call_vsync_frame_cb(void);
extern volatile int adxps2_exec_vint;
extern long long adxm_vint_cnt;
extern int (*adxm_old_cbf)(int arg);
extern volatile int adxt_vsync_cnt;
int SVM_ExecSvrVint();
int adxm_exec_vint(int arg);
int ADXM_SetupThrd(AdxmThreadPrm *tprm);
void adxm_delete_mwidle_thrd(void);
void adxm_delete_vsync_thrd(void);
void adxm_delete_fs_thrd(void);
void adxm_delete_safe_thrd(void);

void adxm_lock(void) {
    int threadId;
    if (adxm_lock_level == 0) {
        threadId = GetThreadId();
        adxm_lock_saved_prio = ChangeThreadPriority(threadId, adxm_tprm.lockPrio);
        adxm_lock_thid = threadId;
        adxm_resume_thrd(adxm_safe_thid);
        adxm_safe_thid; /* matching construct: retail re-reads the thread id after the call (dead load) */
    }
    adxm_lock_level++;
}

void adxm_unlock(void) {
    if (--adxm_lock_level == 0) {
        adxm_suspend_thrd(adxm_safe_thid);
        adxm_safe_thid; /* matching construct: retail re-reads the thread id after the call (dead load) */
        ChangeThreadPriority(GetThreadId(), adxm_lock_saved_prio);
    }
    if (adxm_lock_level < 0) {
        adxm_lock_level = 0;
    }
}

void adxm_goto_svr_border(int threadId, int priority)
{
    int i;
    if (threadId == 0) {
        return;
    }
    adxm_border_request = 1;
    ChangeThreadPriority(threadId, adxm_tprm.lockPrio);
    for (i = 0; ; i++) {
        adxm_wakeup_thrd(threadId);
        adxm_resume_thrd(threadId);
        if (adxm_border_request == 0) {
            break;
        }
        if (i > 199999999) {
            SVM_CallErr1(text_1060102_Internal_Error_adxm_goto);
            break;
        }
    }
    ChangeThreadPriority(threadId, priority);
}

void adxm_goto_mwidle_border(void) {
    adxm_goto_svr_border(adxm_mwidle_thid, adxm_tprm.mwIdlePrio);
}

void adxm_goto_usridle_border(void) {
    adxm_goto_svr_border(adxm_usridle_thid, adxm_tprm.usrIdlePrio);
}

void adxm_safe_count_up(void) {
    adxm_safe_loop_count += 1;
}

void adxm_safe_thrd(void *arg) {
    while (adxm_safe_exit_request == 0) {
        adxm_safe_count_up();
    }
    adxm_safe_exited = 1;
    ExitDeleteThread();
}

void adxm_usrvsync_thrd(void *arg) {
    while (adxm_usrvsync_exit_request == 0) {
        adxm_usrvsync_count++;
        adxm_usrvsync_busy = 1;
        SVM_ExecSvrUsrVsync();
        adxm_usrvsync_busy = 0;
        adxm_sleep_thrd();
    }
    adxm_usrvsync_exited = 1;
    ExitDeleteThread();
}

void adxm_vsync_thrd(void *arg)
{
    while (adxm_vsync_exit_request == 0) {
        adxm_vsync_count++;
        adxm_suspend_thrd(adxm_mwidle_thid);
        if (adxm_mwidle_slept == 0) {
            adxm_call_mwidle_sleep_cb();
        }
        adxm_mwidle_slept = 0;
        if (adxm_is_usridle_mode() == 1) {
            adxm_suspend_thrd(adxm_usridle_thid);
        }
        adxm_wakeup_vsync_waiter();
        adxm_vsync_busy = 1;
        SVM_ExecSvrVsync();
        adxm_vsync_busy = 0;
        adxm_sleep_thrd();
    }
    adxm_vsync_exited = 1;
    ExitDeleteThread();
}

void adxm_fs_thrd(void *arg)
{
    while (adxm_fs_exit_request == 0) {
        adxm_fs_count++;
        adxm_fs_busy = 1;
        if (adxm_fs_bgcolor != 0) {
            *(volatile unsigned long long *)0x120000E0 = adxm_fs_bgcolor;
        }
        SVM_ExecSvrFs();
        if (adxm_fs_bgcolor != 0) {
            *(volatile unsigned long long *)0x120000E0 = 0;
        }
        adxm_fs_busy = 0;
        adxm_sleep_thrd();
    }
    adxm_fs_exited = 1;
    ExitDeleteThread();
}

void adxm_mwidle_thrd(void *arg)
{
    int busy;
    while (adxm_mwidle_exit_request == 0) {
        adxm_mwidle_count++;
        adxm_mwidle_busy = 1;
        busy = SVM_ExecSvrMwIdle();
        adxm_mwidle_busy = 0;
        if (adxm_border_request == 1) {
            adxm_border_request = 0;
            adxm_sleep_thrd();
        }
        if (busy == 0) {
            if (adxm_is_usridle_mode() == 1) {
                if (adxm_resume_thrd(adxm_usridle_thid) == adxm_usridle_thid) {
                    adxm_wakeup_thrd(adxm_usridle_thid);
                }
            }
            if (adxm_border_request != 1) {
                adxm_call_mwidle_sleep_cb();
                adxm_mwidle_slept = 1;
            }
            adxm_sleep_thrd();
        }
    }
    adxm_mwidle_exited = 1;
    ExitDeleteThread();
}

void adxm_usridle_thrd(void *arg)
{
    int busy;
    while (adxm_usridle_exit_request == 0) {
        adxm_usridle_count++;
        adxm_usridle_busy = 1;
        busy = SVM_ExecSvrUsrIdle();
        adxm_usridle_busy = 0;
        if (adxm_border_request == 1) {
            adxm_border_request = 0;
            adxm_sleep_thrd();
        }
        if (busy == 0) {
            adxm_sleep_thrd();
        }
    }
    adxm_usridle_exited = 1;
    ExitDeleteThread();
}

void adxm_iwakeup_thrd(int threadId) {
    struct ThreadParam status;
    if (threadId != 0) {
        iReferThreadStatus(threadId, &status);
        if (status.status == THREAD_WAITING || status.status == THREAD_WAIT_SUSPENDED) {
            iWakeupThread(threadId);
        }
    }
}

void adxm_wakeup_thrd(int threadId) {
    struct ThreadParam status;
    if (threadId != 0) {
        ReferThreadStatus(threadId, &status);
        if (status.status == THREAD_WAITING || status.status == THREAD_WAIT_SUSPENDED) {
            WakeupThread(threadId);
        }
    }
}

void adxm_sleep_thrd(void) {
    SleepThread();
}

int adxm_resume_thrd(int threadId) {
    struct ThreadParam status;
    int result = 0;
    if (threadId != 0) {
        ReferThreadStatus(threadId, &status);
        if (status.status == THREAD_SUSPENDED || status.status == THREAD_WAIT_SUSPENDED) {
            result = ResumeThread(threadId);
        }
    }
    return result;
}

int adxm_suspend_thrd(int threadId) {
    struct ThreadParam status;
    int result = 0;
    if (threadId != 0) {
        ReferThreadStatus(threadId, &status);
        if (status.status != THREAD_SUSPENDED && status.status != THREAD_WAIT_SUSPENDED) {
            result = SuspendThread(threadId);
        }
    }
    return result;
}

void adxm_create_safe_thrd(void) {
    struct ThreadParam param;
    param.entry = adxm_safe_thrd;
    param.stack = adxm_safe_stack;
    param.stackSize = 2048;
    param.initPriority = adxm_main_init_prio;
    param.gpReg = _gp;
    adxm_safe_thid = CreateThread(&param);
    adxm_safe_thid; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(adxm_safe_thid, 0);
    if (adxm_safe_thid != 0) {
        adxm_suspend_thrd(adxm_safe_thid);
        adxm_safe_thid; /* matching construct: dead re-read, as above */
    }
    ChangeThreadPriority(adxm_safe_thid, adxm_tprm.safePrio);
}

void adxm_create_usrvsync_thrd(void *stack, int stackSize) {
    struct ThreadParam param;
    param.entry = adxm_usrvsync_thrd;
    if (stack == 0) {
        param.stack = adxm_usrvsync_stack;
        param.stackSize = 4096;
    } else {
        param.stack = stack;
        param.stackSize = stackSize;
        ADXMSG_PrintErr(ADXM_UsrVsyncThread_Stack_pointe, stack, stackSize);
    }
    param.initPriority = adxm_main_init_prio;
    param.gpReg = _gp;
    adxm_usrvsync_thid = CreateThread(&param);
    adxm_usrvsync_thid; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(adxm_usrvsync_thid, 0);
    ChangeThreadPriority(adxm_usrvsync_thid, adxm_tprm.usrVsyncPrio);
}

void adxm_create_vsync_thrd(void) {
    struct ThreadParam param;
    param.entry = adxm_vsync_thrd;
    param.stack = adxm_vsync_stack;
    param.stackSize = 4096;
    param.initPriority = adxm_main_init_prio;
    param.gpReg = _gp;
    adxm_vsync_thid = CreateThread(&param);
    adxm_vsync_thid; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(adxm_vsync_thid, 0);
    ChangeThreadPriority(adxm_vsync_thid, adxm_tprm.vsyncPrio);
}

void adxm_create_fs_thrd(void) {
    struct ThreadParam param;
    param.entry = adxm_fs_thrd;
    param.stack = adxm_fs_stack;
    param.stackSize = 4096;
    param.initPriority = adxm_main_init_prio;
    param.gpReg = _gp;
    adxm_fs_thid = CreateThread(&param);
    adxm_fs_thid; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(adxm_fs_thid, 0);
    ChangeThreadPriority(adxm_fs_thid, adxm_tprm.fsPrio);
}

void adxm_create_mwidle_thrd(void) {
    struct ThreadParam param;
    param.entry = adxm_mwidle_thrd;
    param.stack = adxm_mwidle_stack;
    param.stackSize = 8192;
    param.initPriority = adxm_main_init_prio;
    param.gpReg = _gp;
    adxm_mwidle_thid = CreateThread(&param);
    adxm_mwidle_thid; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(adxm_mwidle_thid, 0);
    ChangeThreadPriority(adxm_mwidle_thid, adxm_tprm.mwIdlePrio);
    adxm_suspend_thrd(adxm_mwidle_thid);
    adxm_mwidle_thid; /* matching construct: dead re-read, as above */
}

void adxm_create_usridle_thrd(void *stack, int stackSize) {
    struct ThreadParam param;
    param.entry = adxm_usridle_thrd;
    if (stack == 0) {
        param.stack = adxm_usridle_stack;
        param.stackSize = 8192;
    } else {
        param.stack = stack;
        param.stackSize = stackSize;
        ADXMSG_PrintErr(ADXM_UsrIdleThread_Stack_pointer, stack, stackSize);
    }
    param.initPriority = adxm_main_init_prio;
    param.gpReg = _gp;
    adxm_usridle_thid = CreateThread(&param);
    adxm_usridle_thid; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(adxm_usridle_thid, 0);
    ChangeThreadPriority(adxm_usridle_thid, adxm_tprm.usrIdlePrio);
    adxm_suspend_thrd(adxm_usridle_thid);
    adxm_mwidle_thid; /* matching construct: retail re-reads the other thread's id here (dead load) */
}

int adxm_is_usridle_mode(void) {
    return adxm_usridle_mode;
}

void ADXM_ExecSvrUsrVsync(void) {
    SVM_ExecSvrUsrVsync();
}

void ADXM_ExecSvrVsync(void) {
    SVM_ExecSvrVsync();
}

void ADXM_ExecSvrFs(void) {
    SVM_ExecSvrFs();
}

void ADXM_ExecSvrMain(void) {
    SVM_ExecSvrMain();
}

void ADXM_ExecSvrMwIdle(void) {
    SVM_ExecSvrMwIdle();
}

void ADXM_ExecSvrUsrIdle(void) {
    SVM_ExecSvrUsrIdle();
}

int ADXM_ExecSvrAll(void) {
    SVM_ExecSvrUsrVsync();
    SVM_ExecSvrVsync();
    SVM_ExecSvrMain();
    SVM_ExecSvrMwIdle();
    SVM_ExecSvrUsrIdle();
    return 0;
}

int ADXM_IsSetupThrd(void) {
    return adxm_setup_count != 0;
}

void ADXM_SetCbErr(void) {
    SVM_SetCbErr();
}

void adxm_request_thrd_exit(void) {
    adxm_safe_exit_request = 1;
    adxm_usrvsync_exit_request = 1;
    adxm_vsync_exit_request = 1;
    adxm_fs_exit_request = 1;
    adxm_mwidle_exit_request = 1;
    adxm_usridle_exit_request = 1;
}

void ADXM_ShutdownThrd(void) {
    if (--adxm_setup_count == 0) {
        adxm_request_thrd_exit();
        adxm_delete_mwidle_thrd();
        adxm_delete_fs_thrd();
        adxm_delete_vsync_thrd();
        adxm_delete_safe_thrd();
        ChangeThreadPriority(adxm_main_thid, adxm_main_init_prio);
        SVM_SetCbLock(0, 0);
        SVM_SetCbUnlock(0, 0);
        SVM_Finish();
    }
}

void adxm_delete_usridle_thrd(void) {
    while (adxm_usridle_exited == 0) {
        adxm_usridle_exit_request = 1;
        ChangeThreadPriority(adxm_usridle_thid, 1);
        WakeupThread(adxm_usridle_thid);
        adxm_resume_thrd(adxm_usridle_thid);
    }
    adxm_usridle_exited = 0;
    adxm_usridle_exit_request = 0;
    adxm_usridle_thid = 0;
}

void adxm_delete_mwidle_thrd(void) {
    while (adxm_mwidle_exited == 0) {
        adxm_mwidle_exit_request = 1;
        ChangeThreadPriority(adxm_mwidle_thid, 1);
        WakeupThread(adxm_mwidle_thid);
        adxm_resume_thrd(adxm_mwidle_thid);
    }
    adxm_mwidle_exited = 0;
    adxm_mwidle_exit_request = 0;
    adxm_mwidle_thid = 0;
}

void adxm_delete_vsync_thrd(void) {
    while (adxm_vsync_exited == 0) {
        adxm_vsync_exit_request = 1;
        ChangeThreadPriority(adxm_vsync_thid, 1);
        WakeupThread(adxm_vsync_thid);
        adxm_resume_thrd(adxm_vsync_thid);
    }
    adxm_vsync_exited = 0;
    adxm_vsync_exit_request = 0;
    adxm_vsync_thid = 0;
}

void adxm_delete_fs_thrd(void) {
    while (adxm_fs_exited == 0) {
        adxm_fs_exit_request = 1;
        ChangeThreadPriority(adxm_fs_thid, 1);
        WakeupThread(adxm_fs_thid);
        adxm_resume_thrd(adxm_fs_thid);
    }
    adxm_fs_exited = 0;
    adxm_fs_exit_request = 0;
    adxm_fs_thid = 0;
}

void adxm_delete_usrvsync_thrd(void) {
    while (adxm_usrvsync_exited == 0) {
        adxm_usrvsync_exit_request = 1;
        ChangeThreadPriority(adxm_usrvsync_thid, 1);
        WakeupThread(adxm_usrvsync_thid);
        adxm_resume_thrd(adxm_usrvsync_thid);
    }
    adxm_usrvsync_exited = 0;
    adxm_usrvsync_exit_request = 0;
    adxm_usrvsync_thid = 0;
}

void adxm_delete_safe_thrd(void) {
    while (adxm_safe_exited == 0) {
        adxm_safe_exit_request = 1;
        ChangeThreadPriority(adxm_safe_thid, 1);
        WakeupThread(adxm_safe_thid);
        adxm_resume_thrd(adxm_safe_thid);
    }
    adxm_safe_exited = 0;
    adxm_safe_exit_request = 0;
    adxm_safe_thid = 0;
}

void ADXM_Lock(void) {
    SVM_Lock();
}

void ADXM_Unlock(void) {
    SVM_Unlock();
}

int ADXM_GetLockLevel(void) {
    return adxm_lock_level;
}

int adxm_exec_vint(int arg) {
    adxt_vsync_cnt += 1;
    if (adxps2_exec_vint == 0) {
        adxps2_exec_vint = 1;
        if (adxm_setup_count > 0) {
            if (adxm_vsync_busy != 1) {
                adxm_iwakeup_thrd(adxm_vsync_thid);
            }
            if (adxm_fs_busy != 1) {
                adxm_iwakeup_thrd(adxm_fs_thid);
            }
            if (adxm_is_usridle_mode() == 1 && adxm_usrvsync_busy != 1) {
                adxm_iwakeup_thrd(adxm_usrvsync_thid);
            }
            adxm_vint_cnt += 1;
        }
        SVM_ExecSvrVint();
        adxps2_exec_vint = 0;
    }
    if (adxm_old_cbf != 0) {
        return adxm_old_cbf(arg);
    }
    return 0;
}

int ADXM_ExecVint(int arg) {
    return adxm_exec_vint(arg);
}

void ADXM_ExecMain(void) {
    SVM_ExecSvrMain();
}

void adxm_wakeup_idle_thrds(void) {
    if (adxm_resume_thrd(adxm_mwidle_thid) == adxm_mwidle_thid) {
        adxm_wakeup_thrd(adxm_mwidle_thid);
    }
    if (adxm_is_usridle_mode() == 1 && adxm_resume_thrd(adxm_usridle_thid) == adxm_usridle_thid) {
        adxm_wakeup_thrd(adxm_usridle_thid);
    }
}

void adxm_wakeup_vsync_waiter(void) {
    struct ThreadParam info;
    if (adxm_vsync_waiting == 1) {
        ReferThreadStatus(adxm_main_thid, &info);
        if (info.status == THREAD_WAITING || info.status == THREAD_WAIT_SUSPENDED) {
            if (WakeupThread(adxm_main_thid) == adxm_main_thid) {
                adxm_vsync_waiting = 0;
            }
        }
    }
}

void ADXM_WaitVsync(void) {
    adxm_vsync_waiting = 1;
    adxm_sleep_thrd();
}

void ADXM_ExecVsyncFrame(void) {
    SVM_ExecVsyncBegin();
    adxm_wakeup_idle_thrds();
    adxm_call_vsync_frame_cb();
    ADXM_WaitVsync();
    SVM_ExecVsyncEnd();
}

void ADXPS2_ExecVsyncFrame(void) {
    ADXM_ExecVsyncFrame();
}

int ADXPS2_ExecServer(void) {
    if (adxps2_server_busy == 0) {
        adxps2_server_busy = 1;
        ADXT_ExecServer();
        ADXT_ExecFsSvr();
        adxps2_server_busy = 0;
    }
    return 0;
}

void ADXPS2_SetupThrd(Adxps2ThreadPrm *prm) {
    AdxmThreadPrm tprm;
    AdxmThreadPrm *tprmp;
    if (prm != 0) {
        /* matching construct: permuter — the copy of the main priority is written first */
        tprm.mainPrio = prm->mainPrio;
        tprm.lockPrio = prm->lockPrio;
        tprm.safePrio = prm->safePrio;
        tprm.vsyncPrio = prm->vsyncPrio;
        tprm.fsPrio = tprm.vsyncPrio + 1;
        tprm.mwIdlePrio = ADXPS2_MWIDLE_PRIO;
        tprmp = &tprm;
    } else {
        tprmp = 0;
    }
    ADXM_SetupThrd(tprmp);
}

void ADXPS2_ShutdownThrd(void) {
    ADXM_ShutdownThrd();
}

void ADXPS2_ExecServerLocked(void) {
    ADXM_Lock();
    if (adxps2_server_busy == 0) {
        adxps2_server_busy = 1;
        ADXM_Unlock();
        ADXT_ExecServer();
        ADXT_ExecFsSvr();
        adxps2_server_busy = 0;
    } else {
        ADXM_Unlock();
    }
}

void ADXPS2_Lock(void) {
    SVM_Lock();
}

void ADXPS2_Unlock(void) {
    SVM_Unlock();
}

void ADXM_ShutdownThrdEx(void) {
    if (--adxm_setup_count == 0) {
        adxm_request_thrd_exit();
        adxm_delete_usridle_thrd();
        adxm_delete_mwidle_thrd();
        adxm_delete_fs_thrd();
        adxm_delete_vsync_thrd();
        adxm_delete_usrvsync_thrd();
        adxm_delete_safe_thrd();
        ChangeThreadPriority(adxm_main_thid, adxm_main_init_prio);
        SVM_SetCbLock(0, 0);
        SVM_SetCbUnlock(0, 0);
        adxm_usridle_mode = 0;
        SVM_Finish();
    }
}

void ADXM_SetCbUsrVsync(int func, int object) {
    SVM_SetCbSvrId(1, 0, func, object);
}

void ADXM_SetCbUsrIdle(int func, int object) {
    SVM_SetCbSvrId(7, 0, func, object);
}

void ADXM_GotoUsrIdleBorder(void) {
    SVM_GotoSvrBorder(7);
}

void ADXM_SetCbVsyncFrame(void (*func0)(void *), void *arg0, void (*func1)(void *), void *arg1) {
    adxm_vsync_frame_cb.func = func0;
    adxm_vsync_frame_cb.arg = arg0;
    adxm_mwidle_sleep_cb.func = func1;
    adxm_mwidle_sleep_cb.arg = arg1;
}

void adxm_call_vsync_frame_cb(void) {
    if (adxm_vsync_frame_cb.func != 0) {
        adxm_vsync_frame_cb.func(adxm_vsync_frame_cb.arg);
    }
}

void adxm_call_mwidle_sleep_cb(void) {
    if (adxm_mwidle_sleep_cb.func != 0) {
        adxm_mwidle_sleep_cb.func(adxm_mwidle_sleep_cb.arg);
    }
}
