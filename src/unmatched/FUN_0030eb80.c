/* 0x0030eb80 — FUN_0030eb80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaField_Init();
extern int DAT_00533530[4];
int **FUN_0030eb80(int **arg0) {
    igMetaField_Init();
    *arg0 = &DAT_00533530[0];
    return arg0;
}
