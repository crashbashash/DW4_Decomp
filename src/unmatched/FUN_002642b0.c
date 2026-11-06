/* Interrupt-context wake-up: wakes a thread with FUN_0010bd90 if it is waiting (or waiting and
 * suspended). */
/* EE kernel thread status block filled by ReferThreadStatus (ee_thread_status_t). */
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

#define THREAD_WAITING 0x04        /* THS_WAIT */
#define THREAD_SUSPENDED 0x08      /* THS_SUSPEND */
#define THREAD_WAIT_SUSPENDED 0x0c /* THS_WAITSUSPEND */

int iReferThreadStatus(int threadId, ThreadStatus *status);
int FUN_0010bd90(int threadId);

void FUN_002642b0(int threadId) {
    ThreadStatus status;

    if (threadId != 0) {
        iReferThreadStatus(threadId, &status);
        if (status.status == THREAD_WAITING || status.status == THREAD_WAIT_SUSPENDED) {
            FUN_0010bd90(threadId);
        }
    }
}
