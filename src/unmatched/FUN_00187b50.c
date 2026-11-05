/* 0x00187b50 — FUN_00187b50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00187c70();
int igMetaObject_CreateInstance(int, int);

void FUN_00187b50(int arg0) {
    FUN_00187c70();
    igMetaObject_CreateInstance(*(int *)0x560F88, arg0);
}
