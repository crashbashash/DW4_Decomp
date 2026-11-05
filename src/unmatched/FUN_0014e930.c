/* 0x0014e930 — FUN_0014e930. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014ea50();
int igMetaObject_CreateInstance(int, int);

void FUN_0014e930(int arg0) {
    FUN_0014ea50();
    igMetaObject_CreateInstance(*(int *)0x55FE48, arg0);
}
