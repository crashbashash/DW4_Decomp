/* 0x0019f1d0 — FUN_0019f1d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019f330();
int igMetaObject_CreateInstance(int, int);

void FUN_0019f1d0(int arg0) {
    FUN_0019f330();
    igMetaObject_CreateInstance(*(int *)0x5619F8, arg0);
}
