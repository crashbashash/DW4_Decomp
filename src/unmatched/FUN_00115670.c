typedef struct {
    int f0;
    int f4;
    int id;
    int flags;
    long start;
    long now;
    int f32[8];
} Timer;
long FUN_00115670(int id) {
    Timer *t;
    t = (Timer *)(((unsigned int)id >> 10) << 6);
    if (id < 0 || (id & 0x3ff) != t->id) return -1;
    if (t->flags & 1) return t->start - t->now;
    return 0;
}
