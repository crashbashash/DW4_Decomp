/* 0x00135e20 — FUN_00135e20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00135f40();
int igMetaObject_CreateInstance(int, int);

void FUN_00135e20(int arg0) {
    FUN_00135f40();
    igMetaObject_CreateInstance(*(int *)0x55F048, arg0);
}
