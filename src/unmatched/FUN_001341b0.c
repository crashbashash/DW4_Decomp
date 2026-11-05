/* 0x001341b0 — FUN_001341b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00134370();
int igMetaObject_CreateInstance(int, int);

void FUN_001341b0(int arg0) {
    FUN_00134370();
    igMetaObject_CreateInstance(*(int *)0x55EED8, arg0);
}
