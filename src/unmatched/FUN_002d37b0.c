/* 0x002d37b0 — FUN_002d37b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d37f0(int **);
int igMetaField_Construct();
extern int DAT_00531540[4];
int **FUN_002d37b0(int **arg0) {
    igMetaField_Construct();
    *arg0 = &DAT_00531540[0];
    if (arg0 != 0) {
        FUN_002d37f0(arg0);
    }
    return arg0;
}
