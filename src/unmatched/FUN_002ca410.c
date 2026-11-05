/* 0x002ca410 — FUN_002ca410. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ca530();
int igMetaObject_CreateInstance(int, int);

void FUN_002ca410(int arg0) {
    FUN_002ca530();
    igMetaObject_CreateInstance(*(int *)0x586858, arg0);
}
