/* 0x001a51d0 — FUN_001a51d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a52a0();
int igMetaObject_CreateInstance(int, int);

void FUN_001a51d0(int arg0) {
    FUN_001a52a0();
    igMetaObject_CreateInstance(*(int *)0x561F90, arg0);
}
