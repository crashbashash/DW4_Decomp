/* 0x002b7b70 — FUN_002b7b70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b7c00();
int igMetaObject_CreateInstance(int, int);

void FUN_002b7b70(int arg0) {
    FUN_002b7c00();
    igMetaObject_CreateInstance(*(int *)0x585790, arg0);
}
