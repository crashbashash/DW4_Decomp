/* 0x002911b8 — FUN_002911b8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002911b8(int arg0, int *arg1, int *arg2) {
    void *temp_a0;

    temp_a0 = (void *)(arg0 + 0x78);
    *arg1 = *(int *)((char *)(temp_a0) + 24);
    *arg2 = *(int *)((char *)(temp_a0) + 28);
}
