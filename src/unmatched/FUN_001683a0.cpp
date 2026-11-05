/* 0x001683a0 — FUN_001683a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {

int FUN_001683a0(void *arg0);
}
class DW4VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
int FUN_001683a0(void *arg0) {
    int temp_v0;
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    temp_v0 = ((DW4VC_108_3 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 20)), (int)(1), (int)(0x400));
    if (temp_v0 == 0) {
        return 0;
    }
    *(int *)((char *)(arg0) + 40) = temp_v0;
    *(int *)((char *)(arg0) + 36) = 0;
    return 1;
}
