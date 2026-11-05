/* 0x0014f2c0 — FUN_0014f2c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014f390();
int igMetaObject_CreateInstance(int, int);

void FUN_0014f2c0(int arg0) {
    FUN_0014f390();
    igMetaObject_CreateInstance(*(int *)0x55FE90, arg0);
}
