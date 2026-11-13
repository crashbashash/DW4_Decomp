typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; unsigned int option; } SemaParam;
typedef struct { int status; void (*func)(void *); void *stack; int stackSize; void *gpReg; int initPriority; int currentPriority; unsigned int attr; unsigned int option; int waitType; int waitId; int wakeupCount; } ThreadParam;
typedef struct { int idx; int x; } R;
extern int topThreadId;
extern int topThreadSema;
extern R topThreadRequests;
extern char DAT_00555280[];
extern char DAT_0055c870[];
void topThread(void *);
int FUN_0010aee0(SemaParam *);
int FUN_0010aef0(int);
int FUN_0010ace0(ThreadParam *);
int FUN_0010ad00(int, void *);
int FUN_0010add0(void);
int FUN_0010ad70(int, int);
int FUN_0010bcb8(void) {
    ThreadParam tp;
    SemaParam sp;
    if (topThreadId > 0) return -1;
    sp.init_count = 0;
    sp.max_count = 255;
    topThreadSema = FUN_0010aee0(&sp);
    if (topThreadSema < 0) return -1;
    tp.func = topThread;
    tp.stack = DAT_00555280;
    tp.stackSize = 1024;
    tp.gpReg = DAT_0055c870;
    tp.initPriority = 0;
    topThreadId = FUN_0010ace0(&tp);
    if (topThreadId < 0) {
        FUN_0010aef0(topThreadSema);
        return -1;
    }
    topThreadRequests.idx = 0;
    topThreadRequests.x = 0;
    FUN_0010ad00(topThreadId, &topThreadRequests);
    FUN_0010ad70(FUN_0010add0(), 1);
    return topThreadId;
}
