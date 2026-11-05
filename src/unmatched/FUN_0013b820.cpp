class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int *vX(); };
extern "C" {
struct O { char pad[8]; short f8; short f10; };
void Gap__Core__igObject__vfunc_15(void *);
void FUN_0013b820(void *a) {
    Gap__Core__igObject__vfunc_15(a);
    ((short *)a)[5] = 0;
    ((short *)a)[4] = (((VC *)a)->vX())[2];
}
}
