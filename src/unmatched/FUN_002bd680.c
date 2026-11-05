/* 0x002bd680 — FUN_002bd680. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObjectList_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002bd680(int arg0) {
    igObjectList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x585B60, arg0);
}
