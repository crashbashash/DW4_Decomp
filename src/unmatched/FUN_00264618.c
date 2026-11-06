/* Creates and starts the thread running FUN_00263fc0 on the 4 KB stack DAT_004a02b0 and sets its
 * priority from DAT_0049d9a0. */
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
void FUN_00263fc0(void);
extern char DAT_004a02b0[];       /* thread stack */
extern volatile int DAT_0049da24; /* thread id */
extern int DAT_0049d9a0;          /* thread priority */

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
    ChangeThreadPriority(DAT_0049da24, DAT_0049d9a0);
}
