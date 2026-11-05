/* 0x003279d0 - Gap__Core__igStackMemoryPool__vfunc_55. Stack pool aligned allocation: size defaults to 1, alignment is the larger of the pool and request 16-bit values (movz select on the in-place parameter), size header stored at the downward-growing top; alignment variable is unsigned short; default compiler. Verified byte-identical by tools/verify.py. */
struct P { int p[28]; unsigned short f112; short pad; int p2[4]; char *cur; int *top; };
int Gap__Core__igStackMemoryPool__vfunc_55(struct P *arg0, int arg1, unsigned short arg2) {
    unsigned short a;
    unsigned short al; unsigned int pos, off, tot;
    int *ptop;
    if (arg1 == 0) arg1 = 1;
    a = arg0->f112;
    if (arg1 == 0) return 0;
    arg2 = (arg2 > a) ? arg2 : a;
    al = arg2;
    ptop = arg0->top; pos = (unsigned int)arg0->cur;
    off = (al - 1) & (al - (pos & (al - 1)));
    tot = arg1 + off;
    if ((int)((unsigned int)ptop - pos) < (int)tot) return 0;
    arg0->cur = (char *)(pos + tot);
    *arg0->top = tot;
    arg0->top = arg0->top - 1;
    return pos + off;
}
