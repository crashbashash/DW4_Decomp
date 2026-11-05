/* 0x0019faa0 — FUN_0019faa0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019fc00();
int igMetaObject_CreateInstance(int, int);

void FUN_0019faa0(int arg0) {
    FUN_0019fc00();
    igMetaObject_CreateInstance(*(int *)0x561A38, arg0);
}
