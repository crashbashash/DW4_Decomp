/* 0x00305440 — FUN_00305440. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRefMetaField_Init();
extern int DAT_00532eb0[4];
int **FUN_00305440(int **arg0) {
    igRefMetaField_Init();
    *arg0 = &DAT_00532eb0[0];
    return arg0;
}
