/* 0x0019f630 — FUN_0019f630. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019f7a0();
int igMetaObject_CreateInstance(int, int);

void FUN_0019f630(int arg0) {
    FUN_0019f7a0();
    igMetaObject_CreateInstance(*(int *)0x561A10, arg0);
}
