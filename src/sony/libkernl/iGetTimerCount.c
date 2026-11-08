typedef struct {
    int f0;
    int f4;
    int id;
    int flags;
    long start;
    long now;
    int f32[8];
} Timer;
long iGetTimerSystemTime(void);
long iGetTimerCount(int id) {
    Timer *t;
    long r;
    t = (Timer *)(((unsigned int)id >> 10) << 6);
    if (id < 0 || (id & 0x3ff) != t->id) return -1;
    r = t->now;
    if (t->flags & 1) r += iGetTimerSystemTime() - t->start;
    return r;
}
