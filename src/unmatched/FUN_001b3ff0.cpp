/* 0x001b3ff0 — FUN_001b3ff0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int FUN_001b3c90(...);
int FUN_001b4130(...);
int FUN_001b4220(...);
int FUN_001b42c0(...);
int FUN_001e07a0(...);
void FUN_001b3ff0(void *arg0, int arg1);
}
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
void FUN_001b3ff0(void *arg0, int arg1) {
    void **temp_a0;
    void **temp_a0_2;

    if (FUN_001b4130() == 0) {
        FUN_001e07a0(arg1, arg0);
        return;
    }
    FUN_001b4220(arg0, arg1);
    FUN_001b42c0(arg0, arg1);
    temp_a0 = (void **)(*(int *)((char *)(arg0) + 176));
    ((DW4VC_132_1 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 48)));
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 180));
    ((DW4VC_132_1 *)(temp_a0_2))->vX((int)(*(int *)((char *)(arg0) + 52)));
    FUN_001b3c90(arg0, arg1);
}
