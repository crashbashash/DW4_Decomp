/* 0x00245f50 — FUN_00245f50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int FUN_00245fa0(...);
extern void ** DAT_005871d0[4];
void FUN_00245f50(int arg0, int arg1);
}
class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
void FUN_00245f50(int arg0, int arg1) {
    FUN_00245fa0(((DW4VC_92_0 *)(DAT_005871d0[0]))->vX(), arg0, arg1);
}
