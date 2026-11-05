/* 0x0018a2d0 — FUN_0018a2d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0018a3a0();
int igMetaObject_CreateInstance(int, int);

void FUN_0018a2d0(int arg0) {
    FUN_0018a3a0();
    igMetaObject_CreateInstance(*(int *)0x5610C8, arg0);
}
