struct S { char p[112]; unsigned short align; char q[18]; int top; int *end; };
int Gap__Core__igStackMemoryPool__vfunc_54(struct S *arg0, int arg1) {
    int total, pad, mask;
    int cur;
    unsigned short align;
    if (arg1 == 0) {
        return 0;
    }
    align = arg0->align;
    mask = align - 1;
    cur = arg0->top;
    pad = mask & (align - (cur & mask));
    total = arg1 + pad;
    if ((int)arg0->end - cur < total) {
        return 0;
    }
    arg0->top = cur + total;
    *arg0->end = total;
    arg0->end--;
    return cur + pad;
}
