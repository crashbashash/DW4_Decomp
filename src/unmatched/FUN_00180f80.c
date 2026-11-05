/* 0x00180f80 — FUN_00180f80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_0055fe98[4];
int FUN_00180f80(void) {
    return DAT_0055fe98[0];
}
