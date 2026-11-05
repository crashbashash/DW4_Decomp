/* 0x002cfe10 — FUN_002cfe10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002cff30();
int igMetaObject_CreateInstance(int, int);

void FUN_002cfe10(int arg0) {
    FUN_002cff30();
    igMetaObject_CreateInstance(*(int *)0x586D48, arg0);
}
