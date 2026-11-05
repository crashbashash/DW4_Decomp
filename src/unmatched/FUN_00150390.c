/* 0x00150390 — FUN_00150390. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00150570();
int igMetaObject_CreateInstance(int, int);

void FUN_00150390(int arg0) {
    FUN_00150570();
    igMetaObject_CreateInstance(*(int *)0x55FF68, arg0);
}
