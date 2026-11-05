/* 0x0014df70 — FUN_0014df70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014e050();
int igMetaObject_CreateInstance(int, int);

void FUN_0014df70(int arg0) {
    FUN_0014e050();
    igMetaObject_CreateInstance(*(int *)0x55FD80, arg0);
}
