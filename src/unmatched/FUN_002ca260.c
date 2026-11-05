/* 0x002ca260 — FUN_002ca260. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ca380();
int igMetaObject_CreateInstance(int, int);

void FUN_002ca260(int arg0) {
    FUN_002ca380();
    igMetaObject_CreateInstance(*(int *)0x586850, arg0);
}
