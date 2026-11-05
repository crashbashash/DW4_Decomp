/* 0x00237730 — FUN_00237730. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
extern "C" {
long long FUN_0022e440(long long, int);
class A21 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
class A24 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); };
struct S { char pad12[12]; A21 *f12; char pad16[16]; A21 *f32; char pad36[12]; A24 *f48; char pad52[4]; long long f56; long long f64; int f72; char pad76[4]; long long f80; };
void FUN_00237730(S *arg0);
void FUN_00237730(S *arg0) {
    long long t = arg0->f48->vX();
    arg0->f64 = t - arg0->f56;
    arg0->f56 = t;
    arg0->f80 = arg0->f80 + (FUN_0022e440(arg0->f64, arg0->f72) >> 18);
    arg0->f32->vX();
    arg0->f12->vX();
}
}
