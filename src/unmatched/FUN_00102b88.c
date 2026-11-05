/* 0x00102b88 — FUN_00102b88. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00481c30[4];
int *FUN_00102b88(void) {
    return &DAT_00481c30[0];
}
