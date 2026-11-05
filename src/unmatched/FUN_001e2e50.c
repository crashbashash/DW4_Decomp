/* 0x001e2e50 — FUN_001e2e50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001e2e50(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 16) + (arg1 * 4)))) + 12);
}
