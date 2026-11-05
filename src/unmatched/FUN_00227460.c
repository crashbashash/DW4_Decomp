/* 0x00227460 — FUN_00227460. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00227620();
int igMetaObject_CreateInstance(int, int);

void FUN_00227460(int arg0) {
    FUN_00227620();
    igMetaObject_CreateInstance(*(int *)0x56D948, arg0);
}
