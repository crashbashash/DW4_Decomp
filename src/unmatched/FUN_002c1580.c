/* 0x002c1580 — FUN_002c1580. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c1650();
int igMetaObject_CreateInstance(int, int);

void FUN_002c1580(int arg0) {
    FUN_002c1650();
    igMetaObject_CreateInstance(*(int *)0x586018, arg0);
}
