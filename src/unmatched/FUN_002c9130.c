/* 0x002c9130 — FUN_002c9130. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c9250();
int igMetaObject_CreateInstance(int, int);

void FUN_002c9130(int arg0) {
    FUN_002c9250();
    igMetaObject_CreateInstance(*(int *)0x5867E0, arg0);
}
