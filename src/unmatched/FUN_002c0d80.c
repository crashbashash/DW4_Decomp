/* 0x002c0d80 — FUN_002c0d80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c0ea0();
int igMetaObject_CreateInstance(int, int);

void FUN_002c0d80(int arg0) {
    FUN_002c0ea0();
    igMetaObject_CreateInstance(*(int *)0x585F60, arg0);
}
