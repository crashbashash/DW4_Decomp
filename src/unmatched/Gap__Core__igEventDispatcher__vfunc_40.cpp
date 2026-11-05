class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual unsigned char vX(int, int); };
struct L2 { int p0; int p1; int n; int p3; E **arr; };
struct L1 { int p0; int p1; L2 *l2; };
struct O { int vt; int p1; int p2; L1 *f12; };
extern "C" void Gap__Core__igEventDispatcher__vfunc_40(O *arg0, int arg1, int arg2) {
    int n;
    int i;
    E *e;
    n = arg0->f12->l2->n;
    i = 0;
    while (i < n) {
        e = arg0->f12->l2->arr[i];
        if (e->vX(arg2, 1) & 0xFF) break;
        i += 1;
    }
}
