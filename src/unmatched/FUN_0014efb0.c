/* 0x0014efb0 — FUN_0014efb0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014f0c0();
int igMetaObject_CreateInstance(int, int);

void FUN_0014efb0(int arg0) {
    FUN_0014f0c0();
    igMetaObject_CreateInstance(*(int *)0x55FE70, arg0);
}
