/* 0x001356b0 — FUN_001356b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001357e0();
int igMetaObject_CreateInstance(int, int);

void FUN_001356b0(int arg0) {
    FUN_001357e0();
    igMetaObject_CreateInstance(*(int *)0x55EFE8, arg0);
}
