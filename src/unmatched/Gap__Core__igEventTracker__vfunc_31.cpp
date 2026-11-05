struct R { int v; R() {} };
struct L { char pad0[8]; int n; char pad1[4]; int *data; };
class ET { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual R vA(int, int *); virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual int vB(); char pad4[80]; L *f84; };
extern "C" {
int Gap__Core__igEventTracker__vfunc_31(ET *arg0, int arg1);
}
int Gap__Core__igEventTracker__vfunc_31(ET *arg0, int arg1) {
    int out;
    int k;
    int idx;
    int n;
    int i;

    k = arg0->vB();
    i = 0;
    n = arg0->f84->n;
    for (;;) {
        idx = arg0->f84->data[k];
        if (idx == -1) {
            return -1;
        }
        arg0->vA(idx, &out);
        if (out == arg1) {
            return idx;
        }
        k++;
        if (k >= n) {
            k = 0;
        }
        i++;
        if (i >= n) {
            return -1;
        }
    }
}
