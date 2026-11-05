/* 0x002cec00 — FUN_002cec00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ced70();
int igMetaObject_CreateInstance(int, int);

void FUN_002cec00(int arg0) {
    FUN_002ced70();
    igMetaObject_CreateInstance(*(int *)0x586C00, arg0);
}
