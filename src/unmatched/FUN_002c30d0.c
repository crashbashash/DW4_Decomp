/* 0x002c30d0 — FUN_002c30d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c31f0();
int igMetaObject_CreateInstance(int, int);

void FUN_002c30d0(int arg0) {
    FUN_002c31f0();
    igMetaObject_CreateInstance(*(int *)0x586108, arg0);
}
