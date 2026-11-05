/* 0x002c6750 — FUN_002c6750. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c68f0();
int igMetaObject_CreateInstance(int, int);

void FUN_002c6750(int arg0) {
    FUN_002c68f0();
    igMetaObject_CreateInstance(*(int *)0x5865D0, arg0);
}
