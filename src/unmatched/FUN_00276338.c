/* 0x00276338 — FUN_00276338. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
char FUN_00276338(char arg0) {
    return ((arg0 ^ 0x5C) != 0) ? arg0 : 0x2F;
}
