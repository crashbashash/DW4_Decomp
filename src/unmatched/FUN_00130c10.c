/* 0x00130c10 — FUN_00130c10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00130cf0();
int igMetaObject_CreateInstance(int, int);

void FUN_00130c10(int arg0) {
    FUN_00130cf0();
    igMetaObject_CreateInstance(*(int *)0x55EC68, arg0);
}
