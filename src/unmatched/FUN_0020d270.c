/* 0x0020d270 — FUN_0020d270. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0020d270(long long *arg0) {
    *arg0 = *(unsigned int *)0x10000800 | (*(long long *)0x56C188 << 0x10);
}
