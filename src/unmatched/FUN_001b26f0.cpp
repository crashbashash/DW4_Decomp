/* 0x001b26f0 — FUN_001b26f0. Banked by tools/retype_struct_member.py (shape: base):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
extern "C" {
int FUN_0018ac80(...);
int FUN_001b26f0(int arg0, void *arg1, int arg2);
}
class DW4VC_156_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(int); };
int FUN_001b26f0(int arg0, void *arg1, int arg2) {
    if (*(int *)((char *)(arg1) + 96) == 0) {
        ((DW4VC_156_1 *)(((char *)(arg1) + 0)))->vX((int)(arg2));
        FUN_0018ac80(arg0, (char *)arg1 + 0x20);
    }
    return 1;
}
