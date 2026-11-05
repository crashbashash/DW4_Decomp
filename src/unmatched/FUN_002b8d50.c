/* 0x002b8d50 — FUN_002b8d50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b8f90();
int igMetaObject_CreateInstance(int, int);

void FUN_002b8d50(int arg0) {
    FUN_002b8f90();
    igMetaObject_CreateInstance(*(int *)0x5858B0, arg0);
}
