class Elem { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();  virtual int run(int, int, int, int); int pad; int off; };
struct Arr { char pad[8]; int n; char pad2[4]; Elem **data; };
struct Obj { char pad[8]; int base; char pad2[40]; Arr *arr; };
extern "C" int FUN_002d59f0(Obj *arg0, int arg1, int arg2, int arg3, int arg4) {
    int sum = 0;
    int n;
    int base;
    int i;
    base = arg0->base;
    n = arg0->arr->n;
    for (i = 0; i < n; i++) {
        Elem *e = arg0->arr->data[i];
        int o = e->off;
        sum += e->run((arg1 + o) - base, (arg2 + o) - base, arg3, arg4);
    }
    return sum;
}
