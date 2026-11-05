/* 0x002dc940 — FUN_002dc940. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaField_CopyConstruct();
extern int DAT_00532430[4];
int **FUN_002dc940(int **arg0) {
    igMetaField_CopyConstruct();
    *arg0 = &DAT_00532430[0];
    return arg0;
}
