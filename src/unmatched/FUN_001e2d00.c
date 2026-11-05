/* 0x001e2d00 — FUN_001e2d00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00561230[4];
int FUN_001e2d00(void) {
    return DAT_00561230[0];
}
