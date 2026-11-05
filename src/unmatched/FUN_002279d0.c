/* 0x002279d0 — FUN_002279d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00227af0();
int igMetaObject_CreateInstance(int, int);

void FUN_002279d0(int arg0) {
    FUN_00227af0();
    igMetaObject_CreateInstance(*(int *)0x56D980, arg0);
}
