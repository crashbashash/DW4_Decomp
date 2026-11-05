/* 0x002646a0 — FUN_002646a0 (152 bytes). Creates and starts the thread running FUN_002640a0 on the 8 KB stack DAT_004a12b0, sets its priority from DAT_0049d9a8 and leaves it suspended with FUN_002643d0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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
int FUN_002643d0(int threadId);
void FUN_002640a0(void);
extern char DAT_004a12b0[];       /* thread stack */
extern volatile int DAT_0049da2c; /* thread id */
extern int DAT_0049d9a8;          /* thread priority */

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
    ChangeThreadPriority(DAT_0049da2c, DAT_0049d9a8);
    FUN_002643d0(DAT_0049da2c);
    DAT_0049da2c; /* matching construct: dead re-read, as above */
}
