/* 0x002c0a00 — FUN_002c0a00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c0ad0();
int igMetaObject_CreateInstance(int, int);

void FUN_002c0a00(int arg0) {
    FUN_002c0ad0();
    igMetaObject_CreateInstance(*(int *)0x585F40, arg0);
}
