/* 0x0019fde0 — FUN_0019fde0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a1170();
int igMetaObject_CreateInstance(int, int);

void FUN_0019fde0(int arg0) {
    FUN_001a1170();
    igMetaObject_CreateInstance(*(int *)0x561A50, arg0);
}
