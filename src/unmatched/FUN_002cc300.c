/* 0x002cc300 — FUN_002cc300. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002cc420();
int igMetaObject_CreateInstance(int, int);

void FUN_002cc300(int arg0) {
    FUN_002cc420();
    igMetaObject_CreateInstance(*(int *)0x586940, arg0);
}
