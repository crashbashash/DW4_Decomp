/* 0x002c1070 — FUN_002c1070. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c1190();
int igMetaObject_CreateInstance(int, int);

void FUN_002c1070(int arg0) {
    FUN_002c1190();
    igMetaObject_CreateInstance(*(int *)0x585FA0, arg0);
}
