typedef struct ThreadStatus {
    int status;
    void *entry;
    void *stack;
    int stackSize;
    void *globalPointer;
    int initialPriority;
    int currentPriority;
    unsigned int attributes;
    unsigned int options;
    unsigned int waitType;
    unsigned int waitId;
    unsigned int wakeupCount;
} ThreadStatus;

typedef struct ThreadParam {
    int status;
    void (*entry)(void);
    void *stack;
    int stackSize;
    void *globalPointer;
    int initialPriority;
    int currentPriority;
    unsigned int attributes;
    unsigned int options;
} ThreadParam;

#define THREAD_WAITING 0x04
#define THREAD_SUSPENDED 0x08
#define THREAD_WAIT_SUSPENDED 0x0c

typedef struct AdxmCallback {
    void (*func)(void *arg);
    void *arg;
} AdxmCallback;

typedef struct AdxmThreadPrm {
    int lockPriority;
    int serverPriority;
    int vsyncPriority;
    int f12;
    int f16;
    int userPriority;
    int f24;
    int idlePriority;
    void *vsyncStack;
    int vsyncStackSize;
    void *idleStack;
    int idleStackSize;
} AdxmThreadPrm;

typedef struct Rec_2653c8 {
    int a;
    int b;
    int c;
    int d;
} Rec_2653c8;
typedef struct Desc_2653c8 {
    int a;
    int b;
    int first;
    int next;
    int d;
    int kind;
} Desc_2653c8;

extern int DAT_0049d988;
extern int DAT_0049d984;
extern AdxmThreadPrm DAT_0049d990;
extern int DAT_0049d9c0;
extern volatile int DAT_0049d9c4;
extern int DAT_0049d9c8;
extern volatile int DAT_0049d9d0;
extern volatile int DAT_0049d9d4;
extern volatile int DAT_0049d9d8;
extern volatile int DAT_0049d9cc;
extern volatile int DAT_0049d9dc;
extern volatile long long DAT_0049d9e8;
extern long long DAT_0049d9e0;
extern volatile long long DAT_0049d9f0;
extern volatile long long DAT_0049d9f8;
extern volatile long long DAT_0049da00;
extern volatile long long DAT_0049da08;
extern volatile int DAT_0049da18;
extern volatile int DAT_0049da1c;
extern volatile int DAT_0049da20;
extern volatile int DAT_0049da24;
extern volatile int DAT_0049da28;
extern volatile int DAT_0049da2c;
extern volatile int DAT_0049da30;
extern volatile long long DAT_0049da38;
extern volatile long long DAT_0049da40;
extern volatile long long DAT_0049da48;
extern volatile long long DAT_0049da50;
extern volatile long long DAT_0049da58;
extern volatile long long DAT_0049da60;
extern volatile long long DAT_0049da68;
extern volatile long long DAT_0049da70;
extern volatile long long DAT_0049da78;
extern volatile long long DAT_0049da80;
extern volatile long long DAT_0049da88;
extern volatile long long DAT_0049da90;
extern int DAT_0049da98;
extern unsigned short DAT_0049daa4;
extern volatile int DAT_0049daa8;
extern char DAT_0049dab0[];
extern char DAT_0049e2b0[];
extern char DAT_0049f2b0[];
extern char DAT_004a02b0[];
extern char DAT_004a12b0[];
extern char DAT_004a32b0[];
extern int DAT_004a52b0;
extern int DAT_004a52b4;
extern int DAT_004a52b8;
extern char DAT_004ee2d0[];
extern char DAT_004ee300[];
extern char DAT_004ee340[];
extern char DAT_0055c870[];
extern AdxmCallback DAT_0056dfb0;
extern AdxmCallback DAT_0056dfb8;

int GetThreadId(void);
int ChangeThreadPriority(int threadId, int priority);
int ReferThreadStatus(int threadId, ThreadStatus *status);
int iReferThreadStatus(int threadId, ThreadStatus *status);
int WakeupThread(int threadId);
int iWakeupThread(int threadId);
int ResumeThread(int threadId);
int SuspendThread(int threadId);
int SleepThread();
int CreateThread(ThreadParam *param);
int _StartThread(int threadId, void *argument);
void ExitDeleteThread(void);
int FUN_0027e8e0();
void FUN_0027e8f8(int a, int b);
int FUN_0027ec50();
void FUN_0027e398(const char *message);
int FUN_0027e1c0();
int FUN_0027e1d8();
int FUN_0027e748();
int FUN_0027e860();
int FUN_0027e8a0();
int FUN_0027ea98();
int FUN_0027eab0();
int FUN_0027eae0();
int FUN_0027eaf8();
int FUN_0027eb10();
int FUN_0027eb28();
int FUN_0027ed80();
int FUN_0027edb0();
int FUN_0026cbd8();
int FUN_00262950();
void FUN_002659a0(const char *format, ...);

void FUN_00264300(int threadId);
int FUN_00264368(int threadId);
int FUN_002643d0(int threadId);
void FUN_00264350(void);
int FUN_00264808(void);
void FUN_00265838(void);
void FUN_00265808(void);
int FUN_002650a8();
int FUN_00264910(Desc_2653c8 *desc);
void FUN_00264c58(void);
void FUN_00264d28(void);
void FUN_00264df8(void);
void FUN_00264f98(void);

void FUN_00263b80(void) {
    int threadId;
    if (DAT_0049d9c0 == 0) {
        threadId = GetThreadId();
        DAT_004a52b0 = ChangeThreadPriority(threadId, DAT_0049d990.lockPriority);
        DAT_004a52b4 = threadId;
        FUN_00264368(DAT_0049da18);
        DAT_0049da18; /* matching construct: retail re-reads the thread id after the call (dead load) */
    }
    DAT_0049d9c0++;
}

void FUN_00263c08(void) {
    if (--DAT_0049d9c0 == 0) {
        FUN_002643d0(DAT_0049da18);
        DAT_0049da18; /* matching construct: retail re-reads the thread id after the call (dead load) */
        ChangeThreadPriority(GetThreadId(), DAT_004a52b0);
    }
    if (DAT_0049d9c0 < 0) {
        DAT_0049d9c0 = 0;
    }
}

void FUN_00263c78(int thid, int prio)
{
    int i;
    if (thid == 0) {
        return;
    }
    DAT_0049d9c4 = 1;
    ChangeThreadPriority(thid, DAT_0049d990.lockPriority);
    for (i = 0; ; i++) {
        FUN_00264300(thid);
        FUN_00264368(thid);
        if (DAT_0049d9c4 == 0) {
            break;
        }
        if (i > 0x0BEBC1FF) {
            FUN_0027e398(DAT_004ee2d0);
            break;
        }
    }
    ChangeThreadPriority(thid, prio);
}

void FUN_00263d60(void) {
    FUN_00263c78(DAT_0049da2c, DAT_0049d990.f24);
}

void FUN_00263d88(void) {
    FUN_00263c78(DAT_0049da30, DAT_0049d990.idlePriority);
}

void FUN_00263db0(void) {
    DAT_0049d9e0 += 1;
}

void FUN_00263dc8(void) {
    while (DAT_0049da38 == 0) {
        FUN_00263db0();
    }
    DAT_0049da40 = 1;
    ExitDeleteThread();
}

void FUN_00263e20(void) {
    while (DAT_0049da48 == 0) {
        DAT_0049d9e8++;
        DAT_0049d9cc = 1;
        FUN_0027ea98();
        DAT_0049d9cc = 0;
        FUN_00264350();
    }
    DAT_0049da50 = 1;
    ExitDeleteThread();
}

void FUN_00263eb8(void)
{
    while (DAT_0049da58 == 0) {
        DAT_0049d9f0++;
        FUN_002643d0(DAT_0049da2c);
        if (DAT_0049daa8 == 0) {
            FUN_00265838();
        }
        DAT_0049daa8 = 0;
        if (FUN_00264808() == 1) {
            FUN_002643d0(DAT_0049da30);
        }
        FUN_00265288();
        DAT_0049d9c8 = 1;
        FUN_0027eab0();
        DAT_0049d9c8 = 0;
        FUN_00264350();
    }
    DAT_0049da60 = 1;
    ExitDeleteThread();
}

void FUN_00263fc0(void)
{
    while (DAT_0049da68 == 0) {
        DAT_0049d9f8++;
        DAT_0049d9d0 = 1;
        if (DAT_0049daa4 != 0) {
            *(volatile unsigned long long *)0x120000E0 = DAT_0049daa4;
        }
        FUN_0027eae0();
        if (DAT_0049daa4 != 0) {
            *(volatile unsigned long long *)0x120000E0 = 0;
        }
        DAT_0049d9d0 = 0;
        FUN_00264350();
    }
    DAT_0049da70 = 1;
    ExitDeleteThread();
}

void FUN_002640a0(void)
{
    int busy;
    while (DAT_0049da78 == 0) {
        DAT_0049da00++;
        DAT_0049d9d4 = 1;
        busy = FUN_0027eb10();
        DAT_0049d9d4 = 0;
        if (DAT_0049d9c4 == 1) {
            DAT_0049d9c4 = 0;
            FUN_00264350();
        }
        if (busy == 0) {
            if (FUN_00264808() == 1) {
                if (FUN_00264368(DAT_0049da30) == DAT_0049da30) {
                    FUN_00264300(DAT_0049da30);
                }
            }
            if (DAT_0049d9c4 != 1) {
                FUN_00265838();
                DAT_0049daa8 = 1;
            }
            FUN_00264350();
        }
    }
    DAT_0049da80 = 1;
    ExitDeleteThread();
}

void FUN_002641d8(void)
{
    int busy;
    while (DAT_0049da88 == 0) {
        DAT_0049da08++;
        DAT_0049d9d8 = 1;
        busy = FUN_0027eb28();
        DAT_0049d9d8 = 0;
        if (DAT_0049d9c4 == 1) {
            DAT_0049d9c4 = 0;
            FUN_00264350();
        }
        if (busy == 0) {
            FUN_00264350();
        }
    }
    DAT_0049da90 = 1;
    ExitDeleteThread();
}

void FUN_002642b0(int threadId) {
    ThreadStatus status;
    if (threadId != 0) {
        iReferThreadStatus(threadId, &status);
        if (status.status == THREAD_WAITING || status.status == THREAD_WAIT_SUSPENDED) {
            iWakeupThread(threadId);
        }
    }
}

void FUN_00264300(int threadId) {
    ThreadStatus status;
    if (threadId != 0) {
        ReferThreadStatus(threadId, &status);
        if (status.status == THREAD_WAITING || status.status == THREAD_WAIT_SUSPENDED) {
            WakeupThread(threadId);
        }
    }
}

void FUN_00264350(void) {
    SleepThread();
}

int FUN_00264368(int threadId) {
    ThreadStatus status;
    int result = 0;
    if (threadId != 0) {
        ReferThreadStatus(threadId, &status);
        if (status.status == THREAD_SUSPENDED || status.status == THREAD_WAIT_SUSPENDED) {
            result = ResumeThread(threadId);
        }
    }
    return result;
}

int FUN_002643d0(int threadId) {
    ThreadStatus status;
    int result = 0;
    if (threadId != 0) {
        ReferThreadStatus(threadId, &status);
        if (status.status != THREAD_SUSPENDED && status.status != THREAD_WAIT_SUSPENDED) {
            result = SuspendThread(threadId);
        }
    }
    return result;
}

void FUN_00264430(void) {
    ThreadParam param;
    param.entry = FUN_00263dc8;
    param.stack = DAT_0049dab0;
    param.stackSize = 2048;
    param.initialPriority = DAT_004a52b8;
    param.globalPointer = DAT_0055c870;
    DAT_0049da18 = CreateThread(&param);
    DAT_0049da18; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(DAT_0049da18, 0);
    if (DAT_0049da18 != 0) {
        FUN_002643d0(DAT_0049da18);
        DAT_0049da18; /* matching construct: dead re-read, as above */
    }
    ChangeThreadPriority(DAT_0049da18, DAT_0049d990.serverPriority);
}

void FUN_002644d8(void *stack, int stackSize) {
    ThreadParam param;
    param.entry = FUN_00263e20;
    if (stack == 0) {
        param.stack = DAT_0049e2b0;
        param.stackSize = 4096;
    } else {
        param.stack = stack;
        param.stackSize = stackSize;
        FUN_002659a0(DAT_004ee300, stack, stackSize);
    }
    param.initialPriority = DAT_004a52b8;
    param.globalPointer = DAT_0055c870;
    DAT_0049da1c = CreateThread(&param);
    DAT_0049da1c; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(DAT_0049da1c, 0);
    ChangeThreadPriority(DAT_0049da1c, DAT_0049d990.vsyncPriority);
}

void FUN_00264590(void) {
    ThreadParam param;
    param.entry = FUN_00263eb8;
    param.stack = DAT_0049f2b0;
    param.stackSize = 4096;
    param.initialPriority = DAT_004a52b8;
    param.globalPointer = DAT_0055c870;
    DAT_0049da20 = CreateThread(&param);
    DAT_0049da20; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(DAT_0049da20, 0);
    ChangeThreadPriority(DAT_0049da20, DAT_0049d990.f12);
}

void FUN_00264618(void) {
    ThreadParam param;
    param.entry = FUN_00263fc0;
    param.stack = DAT_004a02b0;
    param.stackSize = 4096;
    param.initialPriority = DAT_004a52b8;
    param.globalPointer = DAT_0055c870;
    DAT_0049da24 = CreateThread(&param);
    DAT_0049da24; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(DAT_0049da24, 0);
    ChangeThreadPriority(DAT_0049da24, DAT_0049d990.f16);
}

void FUN_002646a0(void) {
    ThreadParam param;
    param.entry = FUN_002640a0;
    param.stack = DAT_004a12b0;
    param.stackSize = 8192;
    param.initialPriority = DAT_004a52b8;
    param.globalPointer = DAT_0055c870;
    DAT_0049da2c = CreateThread(&param);
    DAT_0049da2c; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(DAT_0049da2c, 0);
    ChangeThreadPriority(DAT_0049da2c, DAT_0049d990.f24);
    FUN_002643d0(DAT_0049da2c);
    DAT_0049da2c; /* matching construct: dead re-read, as above */
}

void FUN_00264738(void *stack, int stackSize) {
    ThreadParam param;
    param.entry = FUN_002641d8;
    if (stack == 0) {
        param.stack = DAT_004a32b0;
        param.stackSize = 8192;
    } else {
        param.stack = stack;
        param.stackSize = stackSize;
        FUN_002659a0(DAT_004ee340, stack, stackSize);
    }
    param.initialPriority = DAT_004a52b8;
    param.globalPointer = DAT_0055c870;
    DAT_0049da30 = CreateThread(&param);
    DAT_0049da30; /* matching construct: retail re-reads the thread id after each use (dead load) */
    _StartThread(DAT_0049da30, 0);
    ChangeThreadPriority(DAT_0049da30, DAT_0049d990.idlePriority);
    FUN_002643d0(DAT_0049da30);
    DAT_0049da2c; /* matching construct: retail re-reads the other thread's id here (dead load) */
}

int FUN_00264808(void) {
    return DAT_0049d988;
}

void FUN_00264818(void) {
    FUN_0027ea98();
}

void FUN_00264830(void) {
    FUN_0027eab0();
}

void FUN_00264848(void) {
    FUN_0027eae0();
}

void FUN_00264860(void) {
    FUN_0027eaf8();
}

void FUN_00264878(void) {
    FUN_0027eb10();
}

void FUN_00264890(void) {
    FUN_0027eb28();
}

int FUN_002648a8(void) {
    FUN_0027ea98();
    FUN_0027eab0();
    FUN_0027eaf8();
    FUN_0027eb10();
    FUN_0027eb28();
    return 0;
}

int FUN_002648e8(void) {
    return DAT_0049d984 != 0;
}

void FUN_002648f8(void) {
    FUN_0027e8a0();
}

void FUN_00264aa0(void) {
    DAT_0049da38 = 1;
    DAT_0049da48 = 1;
    DAT_0049da58 = 1;
    DAT_0049da68 = 1;
    DAT_0049da78 = 1;
    DAT_0049da88 = 1;
}

void FUN_00264af0(void) {
    if (--DAT_0049d984 == 0) {
        FUN_00264aa0();
        FUN_00264c58();
        FUN_00264df8();
        FUN_00264d28();
        FUN_00264f98();
        ChangeThreadPriority(DAT_0049da28, DAT_004a52b8);
        FUN_0027e8e0(0, 0);
        FUN_0027e8f8(0, 0);
        FUN_0027ec50();
    }
}

void FUN_00264b88(void) {
    while (DAT_0049da90 == 0) {
        DAT_0049da88 = 1;
        ChangeThreadPriority(DAT_0049da30, 1);
        WakeupThread(DAT_0049da30);
        FUN_00264368(DAT_0049da30);
    }
    DAT_0049da90 = 0;
    DAT_0049da88 = 0;
    DAT_0049da30 = 0;
}

void FUN_00264c58(void) {
    while (DAT_0049da80 == 0) {
        DAT_0049da78 = 1;
        ChangeThreadPriority(DAT_0049da2c, 1);
        WakeupThread(DAT_0049da2c);
        FUN_00264368(DAT_0049da2c);
    }
    DAT_0049da80 = 0;
    DAT_0049da78 = 0;
    DAT_0049da2c = 0;
}

void FUN_00264d28(void) {
    while (DAT_0049da60 == 0) {
        DAT_0049da58 = 1;
        ChangeThreadPriority(DAT_0049da20, 1);
        WakeupThread(DAT_0049da20);
        FUN_00264368(DAT_0049da20);
    }
    DAT_0049da60 = 0;
    DAT_0049da58 = 0;
    DAT_0049da20 = 0;
}

void FUN_00264df8(void) {
    while (DAT_0049da70 == 0) {
        DAT_0049da68 = 1;
        ChangeThreadPriority(DAT_0049da24, 1);
        WakeupThread(DAT_0049da24);
        FUN_00264368(DAT_0049da24);
    }
    DAT_0049da70 = 0;
    DAT_0049da68 = 0;
    DAT_0049da24 = 0;
}

void FUN_00264ec8(void) {
    while (DAT_0049da50 == 0) {
        DAT_0049da48 = 1;
        ChangeThreadPriority(DAT_0049da1c, 1);
        WakeupThread(DAT_0049da1c);
        FUN_00264368(DAT_0049da1c);
    }
    DAT_0049da50 = 0;
    DAT_0049da48 = 0;
    DAT_0049da1c = 0;
}

void FUN_00264f98(void) {
    while (DAT_0049da40 == 0) {
        DAT_0049da38 = 1;
        ChangeThreadPriority(DAT_0049da18, 1);
        WakeupThread(DAT_0049da18);
        FUN_00264368(DAT_0049da18);
    }
    DAT_0049da40 = 0;
    DAT_0049da38 = 0;
    DAT_0049da18 = 0;
}

void FUN_00265068(void) {
    FUN_0027e1c0();
}

void FUN_00265080(void) {
    FUN_0027e1d8();
}

int FUN_00265098(void) {
    return DAT_0049d9c0;
}

void FUN_002651d0(void) {
    FUN_002650a8();
}

void FUN_002651e8(void) {
    FUN_0027eaf8();
}

void FUN_00265200(void) {
    if (FUN_00264368(DAT_0049da2c) == DAT_0049da2c) {
        FUN_00264300(DAT_0049da2c);
    }
    if (FUN_00264808() == 1 && FUN_00264368(DAT_0049da30) == DAT_0049da30) {
        FUN_00264300(DAT_0049da30);
    }
}

void FUN_00265288(void) {
    ThreadStatus info;
    if (DAT_0049d9dc == 1) {
        ReferThreadStatus(DAT_0049da28, &info);
        if (info.status == THREAD_WAITING || info.status == THREAD_WAIT_SUSPENDED) {
            if (WakeupThread(DAT_0049da28) == DAT_0049da28) {
                DAT_0049d9dc = 0;
            }
        }
    }
}

void FUN_00265308(void) {
    DAT_0049d9dc = 1;
    FUN_00264350();
}

void FUN_00265330(void) {
    FUN_0027ed80();
    FUN_00265200();
    FUN_00265808();
    FUN_00265308();
    FUN_0027edb0();
}

void FUN_00265368(void) {
    FUN_00265330();
}

int FUN_00265380(void) {
    if (DAT_0049da98 == 0) {
        DAT_0049da98 = 1;
        FUN_0026cbd8();
        FUN_00262950();
        DAT_0049da98 = 0;
    }
    return 0;
}

void FUN_002653c8(Rec_2653c8 *src) {
    Desc_2653c8 desc;
    Desc_2653c8 *p;
    if (src != 0) {
        /* matching construct: permuter — the copy of src->d is written first */
        desc.d = src->d;
        desc.a = src->a;
        desc.b = src->b;
        desc.first = src->c;
        desc.next = desc.first + 1;
        desc.kind = 25;
        p = &desc;
    } else {
        p = 0;
    }
    FUN_00264910(p);
}

void FUN_00265428(void) {
    FUN_00264af0();
}

void FUN_00265440(void) {
    FUN_00265068();
    if (DAT_0049da98 == 0) {
        DAT_0049da98 = 1;
        FUN_00265080();
        FUN_0026cbd8();
        FUN_00262950();
        DAT_0049da98 = 0;
    } else {
        FUN_00265080();
    }
}

void FUN_002654a8(void) {
    FUN_0027e1c0();
}

void FUN_002654c0(void) {
    FUN_0027e1d8();
}

void FUN_002656c8(void) {
    if (--DAT_0049d984 == 0) {
        FUN_00264aa0();
        FUN_00264b88();
        FUN_00264c58();
        FUN_00264df8();
        FUN_00264d28();
        FUN_00264ec8();
        FUN_00264f98();
        ChangeThreadPriority(DAT_0049da28, DAT_004a52b8);
        FUN_0027e8e0(0, 0);
        FUN_0027e8f8(0, 0);
        DAT_0049d988 = 0;
        FUN_0027ec50();
    }
}

void FUN_00265778(int arg0, int arg1) {
    FUN_0027e748(1, 0, arg0, arg1);
}

void FUN_002657a0(int arg0, int arg1) {
    FUN_0027e748(7, 0, arg0, arg1);
}

void FUN_002657c8(void) {
    FUN_0027e860(7);
}

void FUN_002657e0(void (*func0)(void *), void *arg0, void (*func1)(void *), void *arg1) {
    DAT_0056dfb0.func = func0;
    DAT_0056dfb0.arg = arg0;
    DAT_0056dfb8.func = func1;
    DAT_0056dfb8.arg = arg1;
}

void FUN_00265808(void) {
    if (DAT_0056dfb0.func != 0) {
        DAT_0056dfb0.func(DAT_0056dfb0.arg);
    }
}

void FUN_00265838(void) {
    if (DAT_0056dfb8.func != 0) {
        DAT_0056dfb8.func(DAT_0056dfb8.arg);
    }
}
