/* 0x002b79d0 — FUN_002b79d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b7ab0();
int igMetaObject_CreateInstance(int, int);

void FUN_002b79d0(int arg0) {
    FUN_002b7ab0();
    igMetaObject_CreateInstance(*(int *)0x585788, arg0);
}
