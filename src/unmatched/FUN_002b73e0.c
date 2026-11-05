/* 0x002b73e0 — FUN_002b73e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igUnsignedCharMetaField_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002b73e0(int arg0) {
    igUnsignedCharMetaField_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x585760, arg0);
}
