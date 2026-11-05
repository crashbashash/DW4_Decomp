/* 0x0026c798 — FUN_0026c798. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004a8e54[4];
extern int DAT_004a8e58[4];
void FUN_0026c798(int arg0) {
    DAT_004a8e54[0] = arg0;
    DAT_004a8e58[0] = arg0;
}
