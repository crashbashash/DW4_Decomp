/* 0x0025d040 — FUN_0025d040. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_00498c60)(int, int);
extern int DAT_00498c64[4];
int FUN_0025d040(int arg0) {
    if (DAT_00498c60 != 0) {
        DAT_00498c60(DAT_00498c64[0], arg0);
    }
    return 0;
}
