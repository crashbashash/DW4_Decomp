/* 0x002bc930 — FUN_002bc930. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002bca90();
int igMetaObject_CreateInstance(int, int);

void FUN_002bc930(int arg0) {
    FUN_002bca90();
    igMetaObject_CreateInstance(*(int *)0x585AF0, arg0);
}
