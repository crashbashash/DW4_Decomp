/* 0x002c6ba0 — FUN_002c6ba0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c6cc0();
int igMetaObject_CreateInstance(int, int);

void FUN_002c6ba0(int arg0) {
    FUN_002c6cc0();
    igMetaObject_CreateInstance(*(int *)0x586638, arg0);
}
