/* thread.c - libkernl's thread services that need a thread of their own. An interrupt handler cannot
 * wake, suspend or rotate the thread it interrupted through the kernel, so it queues the request and
 * signals topThread, a top-priority thread that carries the requests out. DelayThread sleeps on a
 * semaphore a timer alarm signals. */

#include "dw4/eekernel.h"

typedef unsigned int u_int;

#define STATUS_EIE 0x10000

#define TOP_THREAD_STACK_SIZE 1024
#define TOP_THREAD_REQUESTS 512

/* DelayThread's errors */
#define DELAY_ERROR_INTERRUPTS_DISABLED 0x80008008
#define DELAY_ERROR_NO_SEMAPHORE 0x80008003

enum ThreadRequestCommand {
    THREAD_REQUEST_WAKEUP,
    THREAD_REQUEST_ROTATE_READY_QUEUE,
    THREAD_REQUEST_SUSPEND
};

/* one request: the command and its thread id or priority */
typedef struct {
    unsigned char command;
    unsigned char arg;
} ThreadRequest;

/* a ring the handlers write and topThread reads */
typedef struct {
    int readIndex;
    int writeIndex;
    ThreadRequest entries[TOP_THREAD_REQUESTS];
} ThreadRequestQueue;

int _iWakeupThread(int thread);
int _iSuspendThread(int thread);
int RotateThreadReadyQueue(int priority);
unsigned long sceTimerUSec2BusClock(u_int sec, u_int usec);
int SetTimerAlarm(unsigned long clock, int (*handler)(int, int, int, int), int arg);
int kprintf(const char *format, ...);

extern char _gp[];

static int topId = 0;
static char stack[TOP_THREAD_STACK_SIZE];
static int topSema;
static ThreadRequestQueue topArg;

/* the calling thread's id from an interrupt handler (the kernel's negative, interrupt-side
 * GetThreadId) */
static inline int iGetThreadId(void)
{
    int thread;
    __asm__("li $3,-47\n\tsyscall\n\tmove %0,$2" : "=r"(thread) : : "$2", "$3", "memory");
    return thread;
}

static void topThread(ThreadRequestQueue *queue)
{
    int i;
    for (;;) {
        WaitSema(topSema);
        i = queue->readIndex & (TOP_THREAD_REQUESTS - 1);
        queue->readIndex = i + 1;
        switch (queue->entries[i].command) {
        case THREAD_REQUEST_WAKEUP:
            WakeupThread(queue->entries[i].arg);
            break;
        case THREAD_REQUEST_ROTATE_READY_QUEUE:
            RotateThreadReadyQueue(queue->entries[i].arg);
            break;
        case THREAD_REQUEST_SUSPEND:
            SuspendThread(queue->entries[i].arg);
            break;
        default:
            kprintf("## internel error in libkernl.a!\n");
            break;
        }
    }
}

int InitThread(void)
{
    struct ThreadParam thread;
    struct SemaParam sema;
    if (topId > 0) return -1;
    sema.initCount = 0;
    sema.maxCount = 255;
    topSema = CreateSema(&sema);
    if (topSema < 0) return -1;
    thread.entry = (void (*)(void *))topThread;
    thread.stack = stack;
    thread.stackSize = TOP_THREAD_STACK_SIZE;
    thread.gpReg = _gp;
    thread.initPriority = 0;
    topId = CreateThread(&thread);
    if (topId < 0) {
        DeleteSema(topSema);
        return -1;
    }
    topArg.readIndex = 0;
    topArg.writeIndex = 0;
    _StartThread(topId, &topArg);
    ChangeThreadPriority(GetThreadId(), 1);
    return topId;
}

int iWakeupThread(int thread)
{
    int self = iGetThreadId();
    int i;
    if (self != thread) return _iWakeupThread(thread);
    if ((unsigned int)self >= 256 || topId == 0) return -1;
    i = topArg.writeIndex & (TOP_THREAD_REQUESTS - 1);
    topArg.writeIndex = i + 1;
    topArg.entries[i].command = THREAD_REQUEST_WAKEUP;
    topArg.entries[i].arg = self;
    iSignalSema(topSema);
    return self;
}

int iRotateThreadReadyQueue(int priority)
{
    int i;
    if ((unsigned int)priority >= 128 || topId == 0) return -1;
    i = topArg.writeIndex & (TOP_THREAD_REQUESTS - 1);
    topArg.writeIndex = i + 1;
    topArg.entries[i].command = THREAD_REQUEST_ROTATE_READY_QUEUE;
    topArg.entries[i].arg = priority;
    iSignalSema(topSema);
    return priority;
}

int iSuspendThread(int thread)
{
    int self = iGetThreadId();
    int i;
    if (self != thread) return _iSuspendThread(thread);
    if ((unsigned int)self >= 256 || topId == 0) return -1;
    i = topArg.writeIndex & (TOP_THREAD_REQUESTS - 1);
    topArg.writeIndex = i + 1;
    topArg.entries[i].command = THREAD_REQUEST_SUSPEND;
    topArg.entries[i].arg = self;
    iSignalSema(topSema);
    return self;
}

static int _DelayThreadHandler(int id, int scheduled, int actual, int sema);

int DelayThread(u_int usec)
{
    struct SemaParam param;
    u_int stat;
    int sema;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    if (!(stat & STATUS_EIE)) return DELAY_ERROR_INTERRUPTS_DISABLED;
    param.maxCount = 1;
    param.option = (u_int)"DelayThread";
    param.initCount = 0;
    sema = CreateSema(&param);
    if (sema < 0) return DELAY_ERROR_NO_SEMAPHORE;
    ret = SetTimerAlarm(sceTimerUSec2BusClock(0, usec), _DelayThreadHandler, sema);
    if (ret < 0) {
        DeleteSema(sema);
        return ret;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return 0;
}

/* the alarm handler runs with interrupts masked and re-enables them before returning */
static int _DelayThreadHandler(int id, int scheduled, int actual, int sema)
{
    iSignalSema(sema);
    __asm__("sync");
    __asm__("ei");
    return 0;
}
