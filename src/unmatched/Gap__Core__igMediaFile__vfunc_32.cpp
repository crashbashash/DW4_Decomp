/* 0x002ec900 — Gap__Core__igMediaFile__vfunc_32. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
extern "C" {
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vA(int, int, int); virtual void d26(); virtual void d27(); virtual void vB(int, int, int); };
struct S { char pad0[24]; int f24; char pad28[16]; unsigned char f44; char pad45; unsigned char f46; char pad47[5]; int f52; char pad56[4]; int f60; O *f64; };
int Gap__Core__igMediaFile__vfunc_32(S *arg0);
int Gap__Core__igMediaFile__vfunc_32(S *arg0) {
    if (arg0->f44 != 0) {
        return 0;
    }
    if (arg0->f46 != 0) {
        arg0->f64->vB(arg0->f24, 0, 0);
        arg0->f64->vA(arg0->f24, arg0->f60, arg0->f52);
    }
    return 0;
}
}
