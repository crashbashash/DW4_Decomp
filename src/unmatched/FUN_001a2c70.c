/* 0x001a2c70 — FUN_001a2c70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a2d90();
int igMetaObject_CreateInstance(int, int);

void FUN_001a2c70(int arg0) {
    FUN_001a2d90();
    igMetaObject_CreateInstance(*(int *)0x561CA8, arg0);
}
