/* Creates and starts the ADXM user V-sync thread (FUN_00263e20) on the given stack, or on the 4 KB
 * default stack DAT_0049e2b0 when none is given (a given stack is logged through FUN_002659a0),
 * and sets its priority from DAT_0049d998. */
/* EE kernel thread creation block (ee_thread_t). */
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
void FUN_00263e20(void);
void FUN_002659a0(const char *format, ...);
extern char DAT_0049e2b0[];       /* default V-sync thread stack */
extern char DAT_004ee300[];       /* "ADXM: UsrVsyncThread Stack pointer = 0x%08x, size = %d\r\n" */
extern volatile int DAT_0049da1c; /* V-sync thread id */
extern int DAT_0049d998;          /* V-sync thread priority */

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
    ChangeThreadPriority(DAT_0049da1c, DAT_0049d998);
}
