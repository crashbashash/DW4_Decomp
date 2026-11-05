/* 0x00278680 — FUN_00278680. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004b0e0c[4];
extern int DAT_004b0e10[4];
void FUN_00278680(int arg0, int arg1) {
    DAT_004b0e0c[0] = arg0;
    DAT_004b0e10[0] = arg1;
}
