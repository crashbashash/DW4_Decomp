/* 0x00188ea0 — FUN_00188ea0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00188f70();
int igMetaObject_CreateInstance(int, int);

void FUN_00188ea0(int arg0) {
    FUN_00188f70();
    igMetaObject_CreateInstance(*(int *)0x561038, arg0);
}
