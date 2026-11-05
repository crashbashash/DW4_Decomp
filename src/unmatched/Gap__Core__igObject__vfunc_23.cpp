class V136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(); };
struct A { char pad[12]; int fc; int f10; int f14; };
extern "C" {
int FUN_00236f80(...);
extern int DAT_00587d08[4];
extern int DAT_00588f38[4];
void Gap__Core__igObject__vfunc_23(A *arg0);
}
void Gap__Core__igObject__vfunc_23(A *arg0) {
    ((V136 *)arg0)->vX();
    arg0->f10 = FUN_00236f80(arg0->fc, DAT_00587d08[0]);
    arg0->f14 = FUN_00236f80(arg0->fc, DAT_00588f38[0]);
}
