/* 0x00267508 — FUN_00267508. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004a5d5c)(int, int);
extern int DAT_004a5d60[4];
int FUN_00267508(int arg0) {
    if (DAT_004a5d5c != 0) {
        DAT_004a5d5c(DAT_004a5d60[0], arg0);
    }
    return 0;
}
