/* 0x002c8af0 — FUN_002c8af0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c8c10();
int igMetaObject_CreateInstance(int, int);

void FUN_002c8af0(int arg0) {
    FUN_002c8c10();
    igMetaObject_CreateInstance(*(int *)0x5867C0, arg0);
}
