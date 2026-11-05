/* 0x0013a640 — FUN_0013a640. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0013a900();
int igMetaObject_CreateInstance(int, int);

void FUN_0013a640(int arg0) {
    FUN_0013a900();
    igMetaObject_CreateInstance(*(int *)0x55F428, arg0);
}
