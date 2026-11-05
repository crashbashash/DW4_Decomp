/* 0x00264368 — FUN_00264368 (100 bytes). Resumes a thread if it is currently suspended (or waiting and suspended); returns the ResumeThread result, or 0 when nothing was done. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* EE kernel thread status block filled by ReferThreadStatus (ps2sdk reference: ee/kernel/include/kernel.h, ee_thread_status_t) */
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

#define THREAD_SUSPENDED 0x08      /* THS_SUSPEND */
#define THREAD_WAIT_SUSPENDED 0x0c /* THS_WAITSUSPEND */

int ReferThreadStatus(int threadId, ThreadStatus *status);
int ResumeThread(int threadId);

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
