class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
struct L;
struct W { char p[8]; L *l; };
struct L {
    char p[8]; int n; char q[4]; int *d;
    int FindIdx(volatile int *pk) {
        int i;
        int cnt = n;
        int key = *pk;
        for (i = 0; i < cnt; i++) {
            if (key == d[i]) return i;
        }
        return -1;
    }
};
struct A { char p[12]; W *w12; W *w16; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_34(A *arg0, int arg1, int arg2, int arg3);
void Gap__Gui__igEventDispatcher__vfunc_34(A *arg0, int arg1, int arg2, int arg3) {
    volatile int sp6C;
    int idx;
    int cnt;
    int i;
    L *l;
    int key;
    l = arg0->w16->l;
    sp6C = arg2;
    idx = l->FindIdx(&sp6C);
    cnt = arg0->w12->l->n;
    for (i = 0; i < cnt; i++) {
        Obj *o = (Obj *)arg0->w12->l->d[i];
        if ((o->vX(idx, arg3, 0) & 0xFF)) break;
    }
}
