/* 0x002743c0 — FUN_002743c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004ab448[4];
void FUN_002743c0(int arg0) {
    DAT_004ab448[0] = arg0;
}
