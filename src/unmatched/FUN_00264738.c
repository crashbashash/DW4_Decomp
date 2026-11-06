/* Creates and starts the ADXM user idle thread (FUN_002641d8, per the log string at DAT_004ee340)
 * on the given stack, or on the 8 KB default stack DAT_004a32b0 when none is given (a given stack
 * is logged through FUN_002659a0), sets its priority from DAT_0049d9ac and leaves it suspended
 * with FUN_002643d0. */
/* EE kernel thread creation block (ps2sdk reference: ee/kernel/include/kernel.h, ee_thread_t) */
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

int CreateThread(ThreadParam *param);
int _StartThread(int threadId, void *argument);
int ChangeThreadPriority(int threadId, int priority);
extern char DAT_0055c870[]; /* _gp */
extern int DAT_004a52b8;    /* thread start priority */
void FUN_002641d8(void);
int FUN_002643d0(int threadId);
void FUN_002659a0(const char *format, ...);
extern char DAT_004a32b0[];       /* default thread stack */
extern char DAT_004ee340[];       /* "ADXM: UsrIdleThread Stack pointer = 0x%08x, size = %d\r\n" */
extern volatile int DAT_0049da30; /* thread id */
extern volatile int DAT_0049da2c; /* thread id of the FUN_002646a0 thread */
extern int DAT_0049d9ac;          /* thread priority */

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
    ChangeThreadPriority(DAT_0049da30, DAT_0049d9ac);
    FUN_002643d0(DAT_0049da30);
    DAT_0049da2c; /* matching construct: retail re-reads the other thread's id here (dead load) */
}
