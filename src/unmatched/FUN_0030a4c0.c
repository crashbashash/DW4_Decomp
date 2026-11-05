/* 0x0030a4c0 — FUN_0030a4c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaField_CopyConstruct();
extern int DAT_00533080[4];
int **FUN_0030a4c0(int **arg0) {
    igMetaField_CopyConstruct();
    *arg0 = &DAT_00533080[0];
    return arg0;
}
