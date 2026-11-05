/* 0x0026a9b8 — FUN_0026a9b8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026a9b8(void *arg0, int *arg1, int *arg2) {
    *arg1 = *(int *)((char *)(arg0) + 28);
    *arg2 = *(int *)((char *)(arg0) + 24);
    return 1;
}
