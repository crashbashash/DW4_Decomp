/* 0x0015d740 — FUN_0015d740. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
class V164 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int); };
extern "C" {
struct S { char pad24[24]; V164 *f24; };
void FUN_0015d740(S *arg0, int arg1, int arg2) {
    int i;

    for (i = 0; i < 6; i++) {
        arg0->f24->vX(i + arg1 * 6, arg2);
    }
}
}
