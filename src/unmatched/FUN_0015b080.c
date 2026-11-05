/* 0x0015b080 — FUN_0015b080. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0015b080(void *arg0, int arg1, int arg2) {
    *(int *)(*(int *)((char *)(arg0) + 12) + (arg1 * 4)) = arg2;
}
