/* 0x002b76a0 — FUN_002b76a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b77c0();
int igMetaObject_CreateInstance(int, int);

void FUN_002b76a0(int arg0) {
    FUN_002b77c0();
    igMetaObject_CreateInstance(*(int *)0x585770, arg0);
}
