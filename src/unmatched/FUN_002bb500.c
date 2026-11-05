/* 0x002bb500 — FUN_002bb500. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002bb670();
int igMetaObject_CreateInstance(int, int);

void FUN_002bb500(int arg0) {
    FUN_002bb670();
    igMetaObject_CreateInstance(*(int *)0x585A40, arg0);
}
