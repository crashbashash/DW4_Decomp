/* 0x00189bd0 — FUN_00189bd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00189cf0();
int igMetaObject_CreateInstance(int, int);

void FUN_00189bd0(int arg0) {
    FUN_00189cf0();
    igMetaObject_CreateInstance(*(int *)0x561088, arg0);
}
