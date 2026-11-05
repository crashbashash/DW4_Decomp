/* 0x001d62f0 — FUN_001d62f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {

void FUN_001d62f0(void *arg0);
}
class DW4VC_112_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
void FUN_001d62f0(void *arg0) {
    void **temp_a0;
    void **temp_a0_2;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 152));
    ((DW4VC_112_0 *)(temp_a0))->vX();
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 168));
    ((DW4VC_112_0 *)(temp_a0_2))->vX();
}
