/* 0x002ba9f0 — FUN_002ba9f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002bad40();
int igMetaObject_CreateInstance(int, int);

void FUN_002ba9f0(int arg0) {
    FUN_002bad40();
    igMetaObject_CreateInstance(*(int *)0x585978, arg0);
}
