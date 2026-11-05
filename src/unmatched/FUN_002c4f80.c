/* 0x002c4f80 — FUN_002c4f80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c50a0();
int igMetaObject_CreateInstance(int, int);

void FUN_002c4f80(int arg0) {
    FUN_002c50a0();
    igMetaObject_CreateInstance(*(int *)0x5863F8, arg0);
}
