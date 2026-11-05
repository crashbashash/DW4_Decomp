/* 0x002d01a0 — FUN_002d01a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d02b0();
int igMetaObject_CreateInstance(int, int);

void FUN_002d01a0(int arg0) {
    FUN_002d02b0();
    igMetaObject_CreateInstance(*(int *)0x586D70, arg0);
}
