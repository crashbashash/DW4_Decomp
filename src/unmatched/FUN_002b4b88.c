/* 0x002b4b88 — FUN_002b4b88. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004bf014[4];
void FUN_002b4b88(int arg0) {
    DAT_004bf014[0] = arg0;
}
