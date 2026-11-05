/* 0x001e3c80 — FUN_001e3c80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00561d30[4];
int FUN_001e3c80(void) {
    return DAT_00561d30[0];
}
