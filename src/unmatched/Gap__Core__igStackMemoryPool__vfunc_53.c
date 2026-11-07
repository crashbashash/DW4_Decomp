struct S { char p[112]; unsigned short align; char q[14]; int size; int top; int *end; unsigned char active; };
int Gap__Core__igStackMemoryPool__vfunc_53(struct S *arg0) {
    int total, pad, mask;
    int cur;
    unsigned short align;
    int size;
    if (arg0->active == 0) { return 0; }
    size = arg0->size;
    if (size == 0) { return 0; }
    if (size == 0) { return 0; }
    align = arg0->align;
    mask = align - 1;
    pad = (align - (arg0->top & mask)) & mask;
    total = size + pad;
    if ((int)arg0->end - arg0->top < total) { return 0; }
    cur = arg0->top + pad;
    arg0->top += total;
    *arg0->end = total;
    arg0->end--;
    return cur;
}
