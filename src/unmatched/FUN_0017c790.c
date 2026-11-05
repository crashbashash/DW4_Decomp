/* 0x0017c790 — FUN_0017c790. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned char FUN_0017c790(int arg0, int arg1) {
    return *(int *)((char *)((arg1 + arg0)) + 540);
}
