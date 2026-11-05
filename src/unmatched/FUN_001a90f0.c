/* 0x001a90f0 — FUN_001a90f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a9290();
int igMetaObject_CreateInstance(int, int);

void FUN_001a90f0(int arg0) {
    FUN_001a9290();
    igMetaObject_CreateInstance(*(int *)0x562370, arg0);
}
