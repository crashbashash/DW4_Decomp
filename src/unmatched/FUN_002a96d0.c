/* 0x002a96d0 — FUN_002a96d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004beb10[4];
void FUN_002a96d0(int arg0) {
    DAT_004beb10[0] = arg0;
}
