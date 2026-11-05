/* 0x002c9ff0 — FUN_002c9ff0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ca110();
int igMetaObject_CreateInstance(int, int);

void FUN_002c9ff0(int arg0) {
    FUN_002ca110();
    igMetaObject_CreateInstance(*(int *)0x586840, arg0);
}
