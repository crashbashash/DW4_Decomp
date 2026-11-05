/* 0x0017c6a0 — FUN_0017c6a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0017c6a0(void *arg0, int arg1, int *arg2, int *arg3) {
    int temp_a1;

    temp_a1 = arg1 * 0x88;
    *arg2 = *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + temp_a1)) + 12);
    *arg3 = *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + temp_a1)) + 16);
}
