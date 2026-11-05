extern "C" { int FUN_001904f0(void *, void *, int); void Gap__Sg__igTransform__vfunc_25(void *arg0, int arg1); }
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void vX(int); };
void Gap__Sg__igTransform__vfunc_25(void *arg0, int arg1) {
    void *self = arg0;
    arg0 = *(void **)((char *)self + 104);
    if (arg0 == 0) {
        void *p = (char *)self + 0x20;
        FUN_001904f0(p, p, arg1);
        return;
    }
    ((VC *)arg0)->vX(arg1);
}
