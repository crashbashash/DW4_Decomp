struct S { char p[112]; unsigned short align; char q[18]; int top; int *end; };
void *memset(void *, int, int);
int Gap__Core__igStackMemoryPool__vfunc_55(struct S *arg0, int size, unsigned short arg2) {
    int total, pad, mask, ret;
    unsigned short align;
    unsigned short pool;
    if (size == 0) { size = 1; }
    pool = arg0->align;
    if (size == 0) { return 0; }
    arg2 = (arg2 > pool) ? arg2 : pool;
    align = arg2;
    mask = align - 1;
    pad = (align - (arg0->top & mask)) & mask;
    total = size + pad;
    if ((int)arg0->end - arg0->top < total) { return 0; }
    ret = arg0->top + pad;
    arg0->top += total;
    *arg0->end = total;
    arg0->end--;
    return ret;
}
