/* 0x004590c0 — FUN_004590c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00459190();

void FUN_004590c0(int arg0) {
    FUN_00459190();
    igMetaObject_CreateInstance(*(int *)0x58C770, arg0);
}
