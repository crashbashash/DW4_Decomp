typedef struct Timer {
    struct Timer *next;
    int f4;
    int id;
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
    int f12;
    int f16;
    Timer *free;
    int f24;
    volatile int current;
} KState;
extern KState DAT_00483508;
long iGetTimerSystemTime(void);
int DIntr(void);
int EIntr(void);
long SetTimerCount(int id, long count) {
    Timer *t;
    int s;
    long old;
    long long now;
    t = (Timer *)(((unsigned int)id >> 10) << 6);
    s = DIntr();
    if (id < 0 || (id & 0x3ff) != t->id || DAT_00483508.current == id) {
        if (s) EIntr();
        return -1;
    }
    old = t->now;
    if (t->flags & 1) {
        now = iGetTimerSystemTime();
        old += now - t->start;
        t->start = now;
        t->now = count;
    } else {
        t->now = count;
    }
    if (s) EIntr();
    return old;
}
