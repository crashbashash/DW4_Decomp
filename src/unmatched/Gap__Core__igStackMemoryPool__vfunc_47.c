struct E { unsigned sz : 31; unsigned f : 1; };
struct P { char p[116]; int raw; char q[12]; int top; struct E *e; unsigned char active; };
long long Gap__Core__igStackMemoryPool__vfunc_47(struct P *arg0) {
    int cur;
    long long total = 0;
    struct E *e;
    int raw;
    if (arg0->active == 0) {
        return 0;
    }
    cur = arg0->top;
    e = arg0->e + 1;
    raw = arg0->raw;
    while (cur != raw) {
        unsigned t = e->sz;
        e++;
        total += t;
        cur -= t;
    }
    return total;
}
