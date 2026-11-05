/* 0x00305480 — FUN_00305480. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRefMetaField_CopyConstruct();
extern int DAT_00532eb0[4];
int **FUN_00305480(int **arg0) {
    igRefMetaField_CopyConstruct();
    *arg0 = &DAT_00532eb0[0];
    return arg0;
}
