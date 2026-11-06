extern "C" {
int FUN_001bf560(void *, int, int);
int FUN_001bf7d0(void *, unsigned char *, unsigned char *, int *, int *, float *, float *, int);
extern float GPR_00554930;
}
struct L { char pad8[8]; int n; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int v140(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int v184(int, int); virtual void v188(int, int, int, float); virtual void v192(int, int, int, float); };
struct O : VC { char pad4[12]; L *f16; };
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_27(O *arg0, int arg1, int arg2, int arg3);
int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_27(O *arg0, int arg1, int arg2, int arg3) {
    unsigned char sp6F; unsigned char sp6E; int sp68; int sp64; float sp60; float sp5C; float f20;
    FUN_001bf7d0(arg0, &sp6F, &sp6E, &sp68, &sp64, &sp60, &sp5C, arg3);
    if (sp6F != 0) {
        FUN_001bf560(arg0, 0, arg1);
        arg0->v184(0, arg2);
    } else if (sp6E != 0) {
        FUN_001bf560(arg0, arg0->f16->n - 1, arg1);
        arg0->v184(arg0->v140() - 1, arg2);
    } else {
        if (sp5C < GPR_00554930) {
            f20 = 0.0f;
        } else {
            f20 = sp60 / sp5C;
        }
        arg0->v192(arg1, sp68, sp64, f20);
        arg0->v188(arg2, sp68, sp64, f20);
    }
    return 1;
}
