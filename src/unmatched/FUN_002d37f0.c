/* 0x002d37f0 — FUN_002d37f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaField_Init();
extern int DAT_00531540[4];
int **FUN_002d37f0(int **arg0) {
    igMetaField_Init();
    *arg0 = &DAT_00531540[0];
    return arg0;
}
