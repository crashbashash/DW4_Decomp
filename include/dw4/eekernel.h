/* eekernel.h - the EE kernel calls and parameter blocks the engine's C files use (Sony eekernel.h). */
#ifndef DW4_EEKERNEL_H
#define DW4_EEKERNEL_H

#define INTC_TIM0 9
#define INTC_TIM1 10

/* ThreadParam.status: the states ReferThreadStatus reports */
#define THREAD_WAITING 0x04
#define THREAD_SUSPENDED 0x08
#define THREAD_WAIT_SUSPENDED 0x0c

struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

/* Sony's one thread block: CreateThread reads the first nine words, ReferThreadStatus fills all twelve. */
struct ThreadParam {
    int status;
    void (*entry)(void *);
    void *stack;
    int stackSize;
    void *gpReg;
    int initPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
    int waitType;
    int waitId;
    int wakeupCount;
};

int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int SignalSema(int sema);
int iSignalSema(int sema);
int WaitSema(int sema);
int iReferSemaStatus(int sema, struct SemaParam *status);
int AddIntcHandler(int cause, int (*handler)(int cause), int next);
int RemoveIntcHandler(int cause, int id);
int CreateThread(struct ThreadParam *param);
int _StartThread(int thread, void *arg);
void ExitDeleteThread(void);
int GetThreadId(void);
int ReferThreadStatus(int thread, struct ThreadParam *status);
int iReferThreadStatus(int thread, struct ThreadParam *status);
int SleepThread(void);
int WakeupThread(int thread);
int iWakeupThread(int thread);
int SuspendThread(int thread);
int ResumeThread(int thread);
int ChangeThreadPriority(int thread, int priority);

#endif
