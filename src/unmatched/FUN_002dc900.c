/* 0x002dc900 — FUN_002dc900. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaField_Init();
extern int DAT_00532430[4];
int **FUN_002dc900(int **arg0) {
    igMetaField_Init();
    *arg0 = &DAT_00532430[0];
    return arg0;
}
