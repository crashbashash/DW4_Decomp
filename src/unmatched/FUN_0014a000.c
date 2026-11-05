/* 0x0014a000 — FUN_0014a000. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014a0e0();
int igMetaObject_CreateInstance(int, int);

void FUN_0014a000(int arg0) {
    FUN_0014a0e0();
    igMetaObject_CreateInstance(*(int *)0x55F8E8, arg0);
}
