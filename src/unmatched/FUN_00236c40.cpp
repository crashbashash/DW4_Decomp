/* 0x00236c40 - FUN_00236c40. Near-miss sweep fix, verified byte-identical to retail by tools/verify.py. */
extern "C" {

struct S236;
void FUN_00236c40(S236 *arg0, int arg1);
}
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
struct S236 { int a, b, c; void *p; };
void FUN_00236c40(S236 *arg0, int arg1) {
    if (((DW4VC_104_0 *)arg0->p)->vX() != 0) {
        ((DW4VC_100_1 *)arg0->p)->vX((int)(arg1));
    }
}
