/* 0x002abf58 — FUN_002abf58. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004bead4[4];
void FUN_002abf58(int arg0) {
    DAT_004bead4[0] = arg0;
}
