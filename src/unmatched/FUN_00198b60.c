/* 0x00198b60 — FUN_00198b60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00198c30();
int igMetaObject_CreateInstance(int, int);

void FUN_00198b60(int arg0) {
    FUN_00198c30();
    igMetaObject_CreateInstance(*(int *)0x5614F8, arg0);
}
