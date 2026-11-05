/* 0x004509c0 — FUN_004509c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int igFieldSynchronizer_EnsureRegistered();

void FUN_004509c0(int arg0) {
    igFieldSynchronizer_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C538, arg0);
}
