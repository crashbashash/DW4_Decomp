/* 0x002c4ca0 — FUN_002c4ca0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c4d80();
int igMetaObject_CreateInstance(int, int);

void FUN_002c4ca0(int arg0) {
    FUN_002c4d80();
    igMetaObject_CreateInstance(*(int *)0x5863B0, arg0);
}
