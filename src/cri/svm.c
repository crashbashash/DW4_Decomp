/* CRI SVM (server manager): the critical section, error reporting and the server functions the CRI
 * libraries register per server type, which the host's threads run. The lock itself is a pair of
 * callbacks the host registers; every lock records its type, and the outermost unlock checks it. */

#define SVM_SVTYPE_NUM 8
#define SVM_SVR_NUM 6
#define SVM_BDR_NUM 8
#define SVM_ERRMSG_LEN 128
#define SVM_ITOA_DIGITS 32

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

enum SvmLockType {
    SVM_LOCK_NONE = 0,
    SVM_LOCK = 1,
    SVM_LOCK_VAR = 2,
    SVM_LOCK_RSC = 3,
    SVM_LOCK_DEV = 4,
    SVM_LOCK_ETC = 5,
    SVM_LOCK_USR = 1000
};

typedef int (*SvmSvrFunc)(void *obj);
typedef void (*SvmFunc)(void *obj);
typedef void (*SvmErrFunc)(void *obj, char *msg);
typedef int (*SvmTasFunc)(int *flag);

typedef struct SvmSvr {
    SvmSvrFunc func;
    void *obj;
} SvmSvr;

typedef struct SvmCb {
    SvmFunc func;
    void *obj;
} SvmCb;

typedef struct SvmErrCb {
    SvmErrFunc func;
    void *obj;
} SvmErrCb;

typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

void *memset(void *dst, int value, unsigned int size);
unsigned int strlen(const char *s);
char *strncpy(char *dst, const char *src, unsigned int size);
char *strncat(char *dst, const char *src, unsigned int size);
int vsprintf(char *buf, const char *format, va_list args);

extern volatile int svm_lock_level;
extern volatile int svm_lock_type;
extern int svm_exec_cnt[SVM_SVTYPE_NUM];
extern int svm_svr_busy[SVM_SVTYPE_NUM];
extern char svm_errmsg[SVM_ERRMSG_LEN];
extern char svm_itoa_work[SVM_ITOA_DIGITS];
extern SvmSvr svm_svr[SVM_SVTYPE_NUM][SVM_SVR_NUM];
extern SvmCb svm_bdr[SVM_BDR_NUM];
extern SvmCb svm_cblock;
extern SvmCb svm_cbunlock;
extern SvmErrCb svm_cberr;
extern SvmTasFunc svm_tas_func;
extern SvmCb svm_cbvsync_begin;
extern SvmCb svm_cbvsync_end;
extern char svm_unlock_type_miss_match[];
extern char svm_itoa_separator[];   /* " " */
extern char SVM_SetCbSvr_too_many_server_function[];
extern char SVM_DelCbSvr_illegal_id[];
extern char SVM_SetCbSvrId_illegal_id[];
extern char SVM_SetCbSvrId_illegal_svtype[];
extern char SVM_SetCbSvrId_over_write_callback_function[];
extern char SVM_ExecSvrFuncId_illegal_id[];
extern char SVM_ExecSvrFuncId_illegal_svtype[];

void SVM_CallErr(const char *format, ...);
void SVM_CallErr1(const char *msg);
void svm_reset(void);

void svm_lock(int type)
{
    if (svm_cblock.func != 0) {
        svm_cblock.func(svm_cblock.obj);
        if (svm_lock_level == 0) {
            svm_lock_type = type;
        }
        svm_lock_level++;
    }
}

void svm_unlock(int type)
{
    if (svm_cbunlock.func != 0) {
        svm_lock_level--;
        if (svm_lock_level == 0) {
            if (svm_lock_type != type) {
                SVM_CallErr(svm_unlock_type_miss_match, svm_lock_type, type);
            }
            svm_lock_type = SVM_LOCK_NONE;
        }
        svm_cbunlock.func(svm_cbunlock.obj);
    }
}

void SVM_Lock(void)
{
    svm_lock(SVM_LOCK);
}

void SVM_Unlock(void)
{
    svm_unlock(SVM_LOCK);
}

void SVM_LockVar(void)
{
    svm_lock(SVM_LOCK_VAR);
}

void SVM_LockRsc(void)
{
    svm_lock(SVM_LOCK_RSC);
}

void SVM_LockDev(void)
{
    svm_lock(SVM_LOCK_DEV);
}

void SVM_LockEtc(void)
{
    svm_lock(SVM_LOCK_ETC);
}

void SVM_LockUsr(void)
{
    svm_lock(SVM_LOCK_USR);
}

void SVM_UnlockVar(void)
{
    svm_unlock(SVM_LOCK_VAR);
}

void SVM_UnlockRsc(void)
{
    svm_unlock(SVM_LOCK_RSC);
}

void SVM_UnlockDev(void)
{
    svm_unlock(SVM_LOCK_DEV);
}

void SVM_UnlockEtc(void)
{
    svm_unlock(SVM_LOCK_ETC);
}

void SVM_UnlockUsr(void)
{
    svm_unlock(SVM_LOCK_USR);
}

void SVM_CallErr(const char *format, ...)
{
    va_list args;

    memset(svm_errmsg, 0, sizeof(svm_errmsg));
    va_start(args, format);
    vsprintf(svm_errmsg, format, args);
    if (svm_cberr.func != 0) {
        svm_cberr.func(svm_cberr.obj, svm_errmsg);
    }
    va_end(args);
}

void SVM_CallErr1(const char *msg)
{
    strncpy(svm_errmsg, msg, sizeof(svm_errmsg) - 1);
    if (svm_cberr.func != 0) {
        svm_cberr.func(svm_cberr.obj, svm_errmsg);
    }
}

void SVM_CallErr2(const char *msg1, const char *msg2)
{
    strncpy(svm_errmsg, msg1, sizeof(svm_errmsg) - 1);
    strncat(svm_errmsg, msg2, sizeof(svm_errmsg) - 1);
    if (svm_cberr.func != 0) {
        svm_cberr.func(svm_cberr.obj, svm_errmsg);
    }
}

/* Writes value in decimal, at most size - 1 characters. The digit loop stores the digit values into buf
 * itself, and the text copied out reversed is whatever svm_itoa_work holds. */
void SVM_ItoA(long value, char *buf, long size)
{
    long i;
    long len;

    for (i = 0; i < SVM_ITOA_DIGITS; i++) {
        buf[i] = value % 10;
        value /= 10;
        if (value == 0) {
            buf[i] = 0;
            break;
        }
    }
    len = strlen(svm_itoa_work);
    if (len >= size - 1) {
        len = size - 1;
    }
    for (i = 0; i < len; i++) {
        buf[i] = svm_itoa_work[len - 1 - i];
    }
    buf[i] = 0;
}

/* Writes "<value1> <value2>"; the second number is limited by a size of 4 less what is written. */
void SVM_ItoA2(long value1, long value2, char *buf, long size)
{
    char *end;

    SVM_ItoA(value1, buf, size);
    strncat(buf, svm_itoa_separator, (int)size - strlen(buf) - 1);
    end = buf + strlen(buf);
    SVM_ItoA(value2, end, 4 - strlen(buf));
}

/* Registers a server function in the first free slot of its type; returns the slot or -1. */
int SVM_SetCbSvr(int svtype, SvmSvrFunc func, void *obj)
{
    int id;

    SVM_Lock();
    for (id = 0; id < SVM_SVR_NUM; id++) {
        SvmSvr *svr = &svm_svr[svtype][id];

        if (svr->func == 0) {
            svr->func = func;
            svr->obj = obj;
            break;
        }
    }
    if (id == SVM_SVR_NUM) {
        SVM_CallErr1(SVM_SetCbSvr_too_many_server_function);
    }
    SVM_Unlock();
    return id == SVM_SVR_NUM ? -1 : id;
}

void SVM_DelCbSvr(int svtype, unsigned int id)
{
    if (id >= SVM_SVR_NUM) {
        SVM_CallErr1(SVM_DelCbSvr_illegal_id);
    }
    SVM_Lock();
    svm_svr[svtype][id].func = 0;
    svm_svr[svtype][id].obj = 0;
    SVM_Unlock();
}

void SVM_SetCbSvrId(int svtype, unsigned int id, SvmSvrFunc func, void *obj)
{
    SvmSvr *svr;

    if (id >= SVM_SVR_NUM) {
        SVM_CallErr1(SVM_SetCbSvrId_illegal_id);
    }
    /* the svtype check tests id */
    if (svtype < 0 || (int)id >= SVM_SVTYPE_NUM) {
        SVM_CallErr1(SVM_SetCbSvrId_illegal_svtype);
    }
    SVM_Lock();
    svr = &svm_svr[svtype][id];
    if (svr->func != 0) {
        SVM_CallErr1(SVM_SetCbSvrId_over_write_callback_function);
    }
    svr->func = func;
    svr->obj = obj;
    SVM_Unlock();
}

void SVM_SetCbBdr(int id, SvmFunc func, void *obj)
{
    SVM_Lock();
    svm_bdr[id].func = func;
    svm_bdr[id].obj = obj;
    SVM_Unlock();
}

void SVM_GotoSvrBorder(int id)
{
    if (svm_bdr[id].func != 0) {
        svm_bdr[id].func(svm_bdr[id].obj);
    }
}

void SVM_SetCbErr(SvmErrFunc func, void *obj)
{
    SVM_Lock();
    svm_cberr.func = func;
    svm_cberr.obj = obj;
    SVM_Unlock();
}

void SVM_SetCbLock(SvmFunc func, void *obj)
{
    svm_cblock.func = func;
    svm_cblock.obj = obj;
}

void SVM_SetCbUnlock(SvmFunc func, void *obj)
{
    svm_cbunlock.func = func;
    svm_cbunlock.obj = obj;
}

/* Runs every server function of a type, flagging the type busy around each; returns their results
 * or-ed together. */
int SVM_ExecSvrFunc(int svtype)
{
    SvmSvr *svr;
    int busy;
    int id;

    busy = 0;
    svr = svm_svr[svtype];
    for (id = 0; id < SVM_SVR_NUM; id++, svr++) {
        if (svr->func != 0) {
            svm_svr_busy[svtype] = 1;
            busy |= svr->func(svr->obj);
            svm_svr_busy[svtype] = 0;
        }
    }
    svm_exec_cnt[svtype]++;
    return busy;
}

int SVM_ExecSvrFuncId(int svtype, unsigned int id)
{
    SvmSvr *svr;
    int busy;

    busy = 0;
    if (id >= SVM_SVR_NUM) {
        SVM_CallErr1(SVM_ExecSvrFuncId_illegal_id);
    }
    /* the svtype check tests id */
    if (svtype < 0 || (int)id >= SVM_SVTYPE_NUM) {
        SVM_CallErr1(SVM_ExecSvrFuncId_illegal_svtype);
    }
    svr = &svm_svr[svtype][id];
    if (svr->func != 0) {
        busy = svr->func(svr->obj);
    }
    return busy;
}

void SVM_ExecSvrVint(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_VINT);
}

void SVM_ExecSvrUsrVsync(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_USRVSYNC);
}

void SVM_ExecSvrVsync(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_VSYNC);
}

void SVM_ExecSvrFsVsync(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_FSVSYNC);
}

void SVM_ExecSvrFs(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_FS);
}

void SVM_ExecSvrMain(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_MAIN);
}

void SVM_ExecSvrMwIdle(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_MWIDLE);
}

void SVM_ExecSvrUsrIdle(void)
{
    SVM_ExecSvrFunc(SVM_SVTYPE_USRIDLE);
}

void svm_reset(void)
{
    int *cnt;
    int i;

    memset(svm_svr_busy, 0, sizeof(svm_svr_busy));
    memset(&svm_cblock, 0, sizeof(svm_cblock));
    memset(&svm_cbunlock, 0, sizeof(svm_cbunlock));
    memset(&svm_cbvsync_begin, 0, sizeof(svm_cbvsync_begin));
    memset(&svm_cbvsync_end, 0, sizeof(svm_cbvsync_end));
    /* only the first six types' counts */
    cnt = svm_exec_cnt;
    for (i = 5; i >= 0; i--) {
        *cnt++ = 0;
    }
    svm_tas_func = 0;
}

/* Sets *flag to 1 and returns 1 if it was not 1 already, through the host's function when one is set. */
int SVM_TestAndSet(int *flag)
{
    int old;
    int ret;

    if (svm_tas_func != 0) {
        ret = svm_tas_func(flag);
    } else {
        SVM_Lock();
        old = *flag;
        *flag = 1;
        ret = old != 1;
        SVM_Unlock();
    }
    return ret;
}

int SVM_SetCbTestAndSet(SvmTasFunc func)
{
    if (svm_tas_func != 0) {
        return 0;
    }
    svm_tas_func = func;
    return 1;
}

/* Only clears a function that is not set, so it changes nothing. */
void SVM_DelCbTestAndSet(void)
{
    SVM_SetCbTestAndSet(0);
}

void SVM_SetCbVsyncBegin(SvmFunc func, void *obj)
{
    svm_cbvsync_begin.func = func;
    svm_cbvsync_begin.obj = obj;
}

void SVM_SetCbVsyncEnd(SvmFunc func, void *obj)
{
    svm_cbvsync_end.func = func;
    svm_cbvsync_end.obj = obj;
}

void SVM_ExecVsyncBegin(void)
{
    if (svm_cbvsync_begin.func != 0) {
        svm_cbvsync_begin.func(svm_cbvsync_begin.obj);
    }
}

void SVM_ExecVsyncEnd(void)
{
    if (svm_cbvsync_end.func != 0) {
        svm_cbvsync_end.func(svm_cbvsync_end.obj);
    }
}
