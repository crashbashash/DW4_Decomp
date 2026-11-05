/* 0x002f4340 - FUN_002f4340. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int memset(...);
int Gap__Core__igObject__vfunc_02(...);
void FUN_002f4340(void **arg0);
}
class DW4VC_212_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int vX(int); };
void FUN_002f4340(void **arg0) {
    int var_s0;

    Gap__Core__igObject__vfunc_02();
    var_s0 = 0x2D;
    do {
        ((DW4VC_212_1 *)(arg0))->vX((int)(var_s0));
        var_s0 -= 1;
    } while (var_s0 >= 0);
    memset((char *)arg0 + 0x14, 0, 0x19E0);
}
