/* 0x001a6bb0 — FUN_001a6bb0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a6dc0();
int igMetaObject_CreateInstance(int, int);

void FUN_001a6bb0(int arg0) {
    FUN_001a6dc0();
    igMetaObject_CreateInstance(*(int *)0x562100, arg0);
}
