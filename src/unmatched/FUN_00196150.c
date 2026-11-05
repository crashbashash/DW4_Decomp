/* 0x00196150 — FUN_00196150. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001964d0();
int igMetaObject_CreateInstance(int, int);

void FUN_00196150(int arg0) {
    FUN_001964d0();
    igMetaObject_CreateInstance(*(int *)0x5612B0, arg0);
}
