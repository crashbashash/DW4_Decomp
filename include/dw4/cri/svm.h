/* CRI SVM (server manager): the critical section, error reporting and the server functions the CRI
 * libraries register per server type; src/cri/svm.c. */
#ifndef DW4_CRI_SVM_H
#define DW4_CRI_SVM_H

#ifdef __cplusplus
extern "C" {
#endif

/* The servers, by the thread or interrupt that runs them. */
enum SvmSvType {
    SVM_SVTYPE_VINT = 0,
    SVM_SVTYPE_USRVSYNC = 1,
    SVM_SVTYPE_VSYNC = 2,
    SVM_SVTYPE_FSVSYNC = 3,
    SVM_SVTYPE_FS = 4,
    SVM_SVTYPE_MAIN = 5,
    SVM_SVTYPE_MWIDLE = 6,
    SVM_SVTYPE_USRIDLE = 7
};

typedef int (*SvmSvrFunc)(void *obj);
typedef void (*SvmFunc)(void *obj);
typedef void (*SvmErrFunc)(void *obj, char *msg);
typedef int (*SvmTasFunc)(int *flag);

void SVM_Lock(void);
void SVM_Unlock(void);
void SVM_LockVar(void);
void SVM_LockSync(void);
void SVM_LockDev(void);
void SVM_LockThrd(void);
void SVM_LockUsr(void);
void SVM_UnlockVar(void);
void SVM_UnlockSync(void);
void SVM_UnlockDev(void);
void SVM_UnlockThrd(void);
void SVM_UnlockUsr(void);
int SVM_GetLockType(void);
void SVM_CallErr(const char *format, ...);
void SVM_CallErr1(const char *msg);
void SVM_CallErr2(const char *msg1, const char *msg2);
int SVM_SetCbSvr(int svtype, SvmSvrFunc func, void *obj);
void SVM_DelCbSvr(int svtype, unsigned int id);
void SVM_SetCbSvrId(int svtype, unsigned int id, SvmSvrFunc func, void *obj);
void SVM_SetCbBdr(int id, SvmFunc func, void *obj);
void SVM_GotoSvrBorder(int id);
void SVM_SetCbErr(SvmErrFunc func, void *obj);
void SVM_SetCbLock(SvmFunc func, void *obj);
void SVM_SetCbUnlock(SvmFunc func, void *obj);
int SVM_ExecSvrFunc(int svtype);
int SVM_ExecSvrFuncId(int svtype, unsigned int id);
int SVM_ExecSvrVint(void);
int SVM_ExecSvrUsrVsync(void);
int SVM_ExecSvrVsync(void);
int SVM_ExecSvrVsync1(void);
int SVM_ExecSvrFs(void);
int SVM_ExecSvrMain(void);
int SVM_ExecSvrMwIdle(void);
int SVM_ExecSvrUsrIdle(void);
int SVM_GetExecCount(int svtype);
void SVM_Init(void);
void SVM_Finish(void);
int SVM_TestAndSet(int *flag);
int SVM_SetCbTestAndSet(SvmTasFunc func);
void SVM_DelCbTestAndSet(void);
void SVM_SetCbVsyncBegin(SvmFunc func, void *obj);
void SVM_SetCbVsyncEnd(SvmFunc func, void *obj);
void SVM_ExecVsyncBegin(void);
void SVM_ExecVsyncEnd(void);

#ifdef __cplusplus
}
#endif

#endif
