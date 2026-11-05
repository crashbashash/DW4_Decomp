/* 0x002607e8 — FUN_002607e8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00499ce0[];
int FUN_0027e2f0();
int strncpy();
extern int (*DAT_00499cd8)(int, int);
extern int DAT_00499cdc[4];
void FUN_002607e8(int arg0) {
    strncpy(DAT_00499ce0, arg0, 0xFF);
    if (DAT_00499cd8 != 0) {
        DAT_00499cd8(DAT_00499cdc[0], DAT_00499ce0);
    }
    FUN_0027e2f0(DAT_00499ce0);
}
