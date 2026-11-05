/* 0x00176c00 — FUN_00176c00. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
extern "C" {
int FUN_0015d700(...);
void FUN_00176c00(void *arg0);
}
class DW4VC_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(); };
void FUN_00176c00(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_120_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d700(arg0);
}
