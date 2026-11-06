class V192 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual int vX(int, int, int, float); };
extern "C" {
struct L { char pad8[8]; int cnt; };
struct S { V192 *vt; char pad4[12]; L *f16; };
int FUN_001bf560(S *, int, int);
int FUN_001bf7d0(S *, unsigned char *, unsigned char *, int *, int *, float *, float *, int);
int Gap__Core__igCompressedAnimationSequenceQS__vfunc_25(S *arg0, int arg1, int arg2) {
    unsigned char sp4F;
    unsigned char sp4E;
    int sp48;
    int sp44;
    float sp40;
    float sp3C;

    FUN_001bf7d0(arg0, &sp4F, &sp4E, &sp48, &sp44, &sp40, &sp3C, arg2);
    if (sp4F != 0) {
        FUN_001bf560(arg0, 0, arg1);
    } else if (sp4E != 0) {
        FUN_001bf560(arg0, arg0->f16->cnt - 1, arg1);
    } else {
        ((V192 *)arg0)->vX(arg1, sp48, sp44, sp40 / sp3C);
    }
    return 1;
}
}
