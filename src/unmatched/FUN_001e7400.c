/* 0x001e7400 — FUN_001e7400. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00562ba0[4];
int FUN_001e7400(void) {
    return DAT_00562ba0[0];
}
