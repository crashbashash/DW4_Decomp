/* 0x002e2bf0 — FUN_002e2bf0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int Gap__Core__igObject__vfunc_10(...);
void FUN_002e2bf0(void **arg0);
}
class DW4VC_92_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
void FUN_002e2bf0(void **arg0) {
    ((DW4VC_92_1 *)(arg0))->vX((int)(0));
    Gap__Core__igObject__vfunc_10(arg0);
}
