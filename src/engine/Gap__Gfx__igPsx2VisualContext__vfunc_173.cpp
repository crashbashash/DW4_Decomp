class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); };
struct N { char pad0[8]; int f8; char pad12[4]; unsigned char f16; char pad17[7]; char f24[912]; long long f936; char pad944[8]; N *f952; };
struct A { char pad[56]; VC *f56; unsigned char f60; char pad61[7]; float f68; char pad72[1480]; N *f1552; };
extern "C" {
int FUN_001f6f50(...);
float __floatdisf(long long);
int Gap__Gfx__igPsx2VisualContext__vfunc_173(A *arg0);
}
int Gap__Gfx__igPsx2VisualContext__vfunc_173(A *arg0) {
    N *var_s0;

    if (arg0->f60 != 0) {
        arg0->f68 = __floatdisf(arg0->f56->vX());
    }
    var_s0 = arg0->f1552;
    if (var_s0 != 0) {
        while (var_s0 != 0) {
            if (var_s0->f16 != 0) {
                if (var_s0->f8 == 0) {
                    FUN_001f6f50(&var_s0->f24[0]);
                    var_s0->f936 = arg0->f56->vX();
                }
                var_s0->f8 = var_s0->f8 - 1;
            }
            var_s0 = var_s0->f952;
        }
    }
    return 1;
}
