class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(); char pad[12]; int f16; };
struct S { char p[16]; O *f16; unsigned char f20; };
extern "C" {
int FUN_001709d0(...);
void Gap__Attrs__igLightStateAttr__vfunc_24(S *arg0, int arg1);
}
void Gap__Attrs__igLightStateAttr__vfunc_24(S *arg0, int arg1) {
    if (arg0->f16 != 0) {
        if (arg0->f16->f16 == -1) {
            arg0->f16->vX();
        }
        FUN_001709d0(arg1, arg0->f16->f16, arg0->f20);
    }
}
