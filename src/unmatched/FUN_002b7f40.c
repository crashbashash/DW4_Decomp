/* 0x002b7f40 — FUN_002b7f40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b8020();
int igMetaObject_CreateInstance(int, int);

void FUN_002b7f40(int arg0) {
    FUN_002b8020();
    igMetaObject_CreateInstance(*(int *)0x5857C8, arg0);
}
