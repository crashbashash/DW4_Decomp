struct R { int v; R(int x) { v = x; } R() {} };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual R vX(int); };
extern "C" { extern int DAT_004fb418[4]; extern C *DAT_00586f68[4]; R FUN_002f0320(int arg1); }
R FUN_002f0320(int arg1) {
    C *p = DAT_00586f68[0];
    if (p != 0) {
        return p->vX(arg1);
    }
    return R(DAT_004fb418[0]);
}
