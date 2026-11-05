/* 0x001384a0 — FUN_001384a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00138570();
int igMetaObject_CreateInstance(int, int);

void FUN_001384a0(int arg0) {
    FUN_00138570();
    igMetaObject_CreateInstance(*(int *)0x55F228, arg0);
}
