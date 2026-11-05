/* 0x0014fa50 — FUN_0014fa50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014fb70();
int igMetaObject_CreateInstance(int, int);

void FUN_0014fa50(int arg0) {
    FUN_0014fb70();
    igMetaObject_CreateInstance(*(int *)0x55FEB8, arg0);
}
