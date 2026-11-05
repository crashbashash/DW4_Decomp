/* 0x00330f60 — FUN_00330f60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00586b20[4];
int FUN_00330f60(void) {
    return DAT_00586b20[0];
}
