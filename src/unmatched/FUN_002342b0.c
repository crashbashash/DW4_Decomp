/* 0x002342b0 — FUN_002342b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int printf();
extern int DAT_004e95d0[4];
extern int DAT_004e95f8[4];
extern int DAT_004e9600[4];
void FUN_002342b0(int arg0, int arg1, int arg2) {
    int *var_a3;

    if (arg2 != 0) {
        var_a3 = &DAT_004e95f8[0];
    } else {
        var_a3 = &DAT_004e9600[0];
    }
    printf(&DAT_004e95d0[0], arg0, arg1, var_a3);
}
