/* 0x0013c260 — FUN_0013c260. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int Gap__Core__igObject__vfunc_10(...);
int igMetaObject_CountInstances(...);
extern int DAT_0055f4c0[4];
void FUN_0013c260(void **arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_0013c260(void **arg0) {
    if (igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1) == 0) {
        DAT_0055f4c0[0] = 0;
    }
    Gap__Core__igObject__vfunc_10(arg0);
}
