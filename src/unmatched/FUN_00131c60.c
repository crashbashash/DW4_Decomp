/* 0x00131c60 — FUN_00131c60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00131d80();
int igMetaObject_CreateInstance(int, int);

void FUN_00131c60(int arg0) {
    FUN_00131d80();
    igMetaObject_CreateInstance(*(int *)0x55ED00, arg0);
}
