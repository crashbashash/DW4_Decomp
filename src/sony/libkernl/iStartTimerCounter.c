typedef struct Timer {
    struct Timer *next;
    int f4;
    volatile int id;
    int flags;
    long long start;
    long long now;
    int f32;
    int f36;
    int f40;
    int f44[5];
} Timer;
typedef struct {
    int f0;
    int f4;
    int f8;
    volatile int f12;
    int f16;
    Timer *free;
    int f24;
    volatile int current;
} KState;
extern KState DAT_00483508;
long iGetTimerSystemTime(void);
void InsertAlarm(Timer *t);
void SetNextComp(long now);
int iStartTimerCounter(int id) {
    Timer *t;
    long long now;
    t = (Timer *)(((unsigned int)id >> 10) << 6);
    if (id < 0 || (id & 0x3ff) != t->id) return 0x80008002;
    if (DAT_00483508.current == id) return 0x80000010;
    if (t->flags & 1) return 1;
    now = iGetTimerSystemTime();
    t->start = now;
    t->flags |= 1;
    if (t->flags & 2) {
        InsertAlarm(t);
        SetNextComp(now);
    }
    return 0;
}
