struct S { char p[112]; unsigned short align; char q[18]; int top; int *end; };
void *memset(void *, int, int);
void *Gap__Core__igStackMemoryPool__vfunc_57(struct S *s, int count, int size, unsigned short a) {
    int total = count * size;
    unsigned short pool;
    if (total == 0) { total = 1; }
    pool = s->align;
    if (total == 0) {
        return 0;
    } else {
        void *p;
        int pad;
        int mask;
        int need;
        unsigned short align;
        a = (a > pool) ? a : pool;
        align = a;
        mask = align - 1;
        pad = (align - (s->top & mask)) & mask;
        need = total + pad;
        if ((int)s->end - s->top < need) { return 0; }
        p = (void *)(s->top + pad);
        s->top += need;
        *s->end = need;
        s->end--;
        memset(p, 0, total);
        return p;
    }
}
