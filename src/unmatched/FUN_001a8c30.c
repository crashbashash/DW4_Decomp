/* 0x001a8c30 — FUN_001a8c30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a8df0();
int igMetaObject_CreateInstance(int, int);

void FUN_001a8c30(int arg0) {
    FUN_001a8df0();
    igMetaObject_CreateInstance(*(int *)0x562338, arg0);
}
