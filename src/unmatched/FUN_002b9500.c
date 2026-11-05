/* 0x002b9500 — FUN_002b9500. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b9620();
int igMetaObject_CreateInstance(int, int);

void FUN_002b9500(int arg0) {
    FUN_002b9620();
    igMetaObject_CreateInstance(*(int *)0x5858F0, arg0);
}
