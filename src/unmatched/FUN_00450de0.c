/* 0x00450de0 — FUN_00450de0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int igFieldChangeView_EnsureRegistered();

void FUN_00450de0(int arg0) {
    igFieldChangeView_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C550, arg0);
}
