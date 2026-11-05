/* 0x0019f480 — FUN_0019f480. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019f5a0();
int igMetaObject_CreateInstance(int, int);

void FUN_0019f480(int arg0) {
    FUN_0019f5a0();
    igMetaObject_CreateInstance(*(int *)0x561A08, arg0);
}
