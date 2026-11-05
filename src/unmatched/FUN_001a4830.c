/* 0x001a4830 — FUN_001a4830. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a4970();
int igMetaObject_CreateInstance(int, int);

void FUN_001a4830(int arg0) {
    FUN_001a4970();
    igMetaObject_CreateInstance(*(int *)0x561EF0, arg0);
}
