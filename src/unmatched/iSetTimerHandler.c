typedef unsigned long (*TimerHandler)(int id, unsigned long schedule, unsigned long actual, void *arg, void *addr);
typedef struct TimerCounter {
    struct TimerCounter *next;
    int f4;
    int id;
    unsigned int flags;
    unsigned long start;
    unsigned long now;
    unsigned long schedule;
    TimerHandler handler;
    void *gp;
    void *arg;
    int f52;
} TimerCounter;
typedef struct {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    TimerCounter *free;
    int f24;
    volatile int current;
} KState;
extern KState DAT_00483508;
void FUN_00114d88(TimerCounter *t);
void InsertAlarm(TimerCounter *t);
unsigned long iGetTimerSystemTime(void);
void SetNextComp(unsigned long now);
int iSetTimerHandler(int id, unsigned long schedule, TimerHandler handler, void *arg) {
    TimerCounter *t = (TimerCounter *)(((unsigned int)id >> 10) << 6);
    if (id < 0 || (id & 0x3ff) != t->id) return 0x80008002;
    if (DAT_00483508.current == id) return 0x80000010;
    if (t->flags & 2) FUN_00114d88(t);
    t->handler = handler;
    if (handler == 0) {
        t->flags &= ~2;
    } else {
        t->schedule = schedule;
        t->flags |= 2;
        __asm__ volatile("sw $28,%0" : "=m"(t->gp) : : "memory");
        t->arg = arg;
        if (t->flags & 1) InsertAlarm(t);
    }
    SetNextComp(iGetTimerSystemTime());
    return 0;
}
