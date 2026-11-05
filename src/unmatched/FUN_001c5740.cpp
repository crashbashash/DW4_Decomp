struct T { char p[8]; void **f; };
struct U { char p[8]; int f; };
extern "C" {
int FUN_00300c00(...);
void FUN_001c5740(U *arg0, T *arg1);
}
class DW4VC_72_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual int vX(); };
void FUN_001c5740(U *arg0, T *arg1) {
    ((DW4VC_72_0 *)(arg1->f))->vX();
    FUN_00300c00(arg0->f, arg1->f, 0);
}
