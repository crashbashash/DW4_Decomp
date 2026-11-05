/* 0x002c01f0 — FUN_002c01f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c0360();
int igMetaObject_CreateInstance(int, int);

void FUN_002c01f0(int arg0) {
    FUN_002c0360();
    igMetaObject_CreateInstance(*(int *)0x585E88, arg0);
}
