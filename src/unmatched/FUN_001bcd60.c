/* 0x001bcd60 — FUN_001bcd60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001bcd60(int arg0, int arg1) {
    return arg0 + (arg1 * 4);
}
