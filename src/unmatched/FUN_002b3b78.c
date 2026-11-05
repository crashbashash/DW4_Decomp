/* 0x002b3b78 — FUN_002b3b78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004bec3c[4];
void FUN_002b3b78(int arg0) {
    DAT_004bec3c[0] = arg0;
}
