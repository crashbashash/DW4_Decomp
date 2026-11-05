/* 0x002befe0 — FUN_002befe0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002bf190();
int igMetaObject_CreateInstance(int, int);

void FUN_002befe0(int arg0) {
    FUN_002bf190();
    igMetaObject_CreateInstance(*(int *)0x585D60, arg0);
}
