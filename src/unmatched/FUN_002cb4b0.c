/* 0x002cb4b0 — FUN_002cb4b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002cb5d0();
int igMetaObject_CreateInstance(int, int);

void FUN_002cb4b0(int arg0) {
    FUN_002cb5d0();
    igMetaObject_CreateInstance(*(int *)0x5868C0, arg0);
}
