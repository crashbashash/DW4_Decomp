/* 0x00132b60 — FUN_00132b60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00132cf0();
int igMetaObject_CreateInstance(int, int);

void FUN_00132b60(int arg0) {
    FUN_00132cf0();
    igMetaObject_CreateInstance(*(int *)0x55EDA0, arg0);
}
