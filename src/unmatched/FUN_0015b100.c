/* 0x0015b100 — FUN_0015b100. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned short FUN_0015b100(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(arg0) + 12) + (arg1 * 2));
}
