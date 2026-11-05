/* 0x002cce40 — FUN_002cce40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ccf60();
int igMetaObject_CreateInstance(int, int);

void FUN_002cce40(int arg0) {
    FUN_002ccf60();
    igMetaObject_CreateInstance(*(int *)0x586998, arg0);
}
