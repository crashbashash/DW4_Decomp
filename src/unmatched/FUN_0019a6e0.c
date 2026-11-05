/* 0x0019a6e0 — FUN_0019a6e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019a800();
int igMetaObject_CreateInstance(int, int);

void FUN_0019a6e0(int arg0) {
    FUN_0019a800();
    igMetaObject_CreateInstance(*(int *)0x5615C8, arg0);
}
