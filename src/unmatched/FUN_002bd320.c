/* 0x002bd320 — FUN_002bd320. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002bd470();
int igMetaObject_CreateInstance(int, int);

void FUN_002bd320(int arg0) {
    FUN_002bd470();
    igMetaObject_CreateInstance(*(int *)0x585B48, arg0);
}
