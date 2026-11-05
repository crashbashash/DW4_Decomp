/* 0x001d3590 — FUN_001d3590. Banked by tools/retype_struct_member.py (shape: base):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
extern "C" {
int Gap__Core__igObject__vfunc_15(...);
void FUN_001d3590(void *arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_001d3590(void *arg0) {
    Gap__Core__igObject__vfunc_15();
    *(int *)((char *)(arg0) + 24) = (int)((int) *(int *)((char *)(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX()) + 8));
}
