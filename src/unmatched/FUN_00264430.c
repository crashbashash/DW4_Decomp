/* Creates and starts the ADX server thread (FUN_00263dc8 on the 2 KB stack DAT_0049dab0), suspends
 * it again with FUN_002643d0 and sets its working priority from DAT_0049d994. */
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
void FUN_00263dc8(void);
int FUN_002643d0(int threadId);
extern char DAT_0049dab0[];       /* server thread stack */
extern volatile int DAT_0049da18; /* ADX server thread id */
extern int DAT_0049d994;          /* server thread priority */

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
    ChangeThreadPriority(DAT_0049da18, DAT_0049d994);
}
