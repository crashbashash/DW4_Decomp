/* 0x001a5d30 — FUN_001a5d30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a5e90();
int igMetaObject_CreateInstance(int, int);

void FUN_001a5d30(int arg0) {
    FUN_001a5e90();
    igMetaObject_CreateInstance(*(int *)0x562078, arg0);
}
