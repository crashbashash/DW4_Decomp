/* 0x0016cdf0 — FUN_0016cdf0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0016cdf0(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
}
