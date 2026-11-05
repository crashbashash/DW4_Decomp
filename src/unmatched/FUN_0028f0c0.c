/* 0x0028f0c0 — FUN_0028f0c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0028f0c0(void *arg0, int arg1, int arg2) {
    void *temp_a0;

    temp_a0 = (void *)((char *)arg0 + 0x3E8);
    *(int *)((char *)(arg0) + 1000) = arg1;
    *(int *)((char *)(temp_a0) + 4) = arg2;
    *(int *)((char *)(temp_a0) + 8) = 0;
}
