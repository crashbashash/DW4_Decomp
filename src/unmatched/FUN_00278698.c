/* 0x00278698 — FUN_00278698. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004b0e0c)(int, int);
extern int DAT_004b0e10[4];
void FUN_00278698(int arg0) {
    if (DAT_004b0e0c != 0) {
        DAT_004b0e0c(DAT_004b0e10[0], arg0);
    }
}
