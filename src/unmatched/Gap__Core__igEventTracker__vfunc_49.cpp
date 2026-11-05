struct RS { int w0; };
struct TB { char p0[8]; int count; char p12[4]; int *data; };
class O { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
 virtual RS v27(int, int *);
 virtual void f28(); virtual void f29(); virtual void f30(); virtual void f31(); virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35(); virtual void f36(); virtual void f37(); virtual void f38(); virtual void f39(); virtual void f40(); virtual void f41(); virtual void f42(); virtual void f43(); virtual void f44(); virtual void f45();
 virtual int v46(int);
 virtual void v47();
 virtual void v48(int);
 char p4[80]; TB *tab; };
extern "C" void Gap__Core__igEventTracker__vfunc_49(O *self, int arg1, int arg2) {
    int sp9C;
    int idx, tried, n, half, cnt;
    TB *tb;
    int *slot;
    int v;
loop:
    n = self->tab->count;
    half = n >> 1;
    if (n < 0) half = (n + 1) >> 1;
    tried = 0;
    bool z = !(n != 0);
    if (z) goto done;
    {
        idx = self->v46(arg1);
again:
        tb = self->tab;
        slot = tb->data + idx;
        v = *slot;
        if (v == -1) {
            cnt = tb->count;
            if (cnt != 0 && idx >= 0 && idx < cnt) *slot = arg2;
        } else {
            self->v27(v, &sp9C);
            if (sp9C == arg1) {
                tb = self->tab;
                cnt = tb->count;
                if (cnt != 0 && idx >= 0 && idx < cnt) tb->data[idx] = arg2;
            } else {
                idx += 1;
                if (idx >= n) idx = 0;
                tried += 1;
                if (tried >= half) {
                    self->v48(n * 2);
                    goto loop;
                }
                goto again;
            }
        }
    }
done: ;
}
