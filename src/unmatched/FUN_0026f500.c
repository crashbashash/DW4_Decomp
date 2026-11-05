/* 0x0026f500 — FUN_0026f500. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004a927c)(int);
extern int DAT_004a9280[4];
void FUN_0026f500(void) {
    if (DAT_004a927c != 0) {
        DAT_004a927c(DAT_004a9280[0]);
    }
}
