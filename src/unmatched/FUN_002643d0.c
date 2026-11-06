/* Suspends a thread unless it is already suspended (or waiting and suspended); returns the
 * SuspendThread result, or 0 when nothing was done. */
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
int SuspendThread(int threadId);

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
