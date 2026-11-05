/* 0x00305400 — FUN_00305400. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00305440(int **);
int igRefMetaField_Construct();
extern int DAT_00532eb0[4];
int **FUN_00305400(int **arg0) {
    igRefMetaField_Construct();
    *arg0 = &DAT_00532eb0[0];
    if (arg0 != 0) {
        FUN_00305440(arg0);
    }
    return arg0;
}
