/* 0x002caa70 — FUN_002caa70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIntList_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002caa70(int arg0) {
    igIntList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x586880, arg0);
}
