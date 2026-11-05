/* 0x001d82c0 — FUN_001d82c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001d82c0(void *arg0, int arg1, int arg2) {
    return *(int *)(*(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 32)) + 16) + (arg1 * 4)))) + 16) + (arg2 * 4));
}
