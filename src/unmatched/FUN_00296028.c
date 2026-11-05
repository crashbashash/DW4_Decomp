/* 0x00296028 — FUN_00296028. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004be890[4];
extern int DAT_004be894[4];
extern int DAT_004be898[4];
extern int DAT_004be89c[4];
void FUN_00296028(void) {
    DAT_004be890[0] = 1;
    DAT_004be894[0] = 0;
    DAT_004be898[0] = 0;
    DAT_004be89c[0] = 0;
}
