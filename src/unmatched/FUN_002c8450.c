/* 0x002c8450 — FUN_002c8450. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDataList_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002c8450(int arg0) {
    igDataList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x586788, arg0);
}
