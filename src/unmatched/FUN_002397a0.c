/* 0x002397a0 — FUN_002397a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00239910();
int igMetaObject_CreateInstance(int, int);

void FUN_002397a0(int arg0) {
    FUN_00239910();
    igMetaObject_CreateInstance(*(int *)0x56DCC8, arg0);
}
