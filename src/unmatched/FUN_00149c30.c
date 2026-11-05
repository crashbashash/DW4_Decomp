/* 0x00149c30 — FUN_00149c30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00149d50();
int igMetaObject_CreateInstance(int, int);

void FUN_00149c30(int arg0) {
    FUN_00149d50();
    igMetaObject_CreateInstance(*(int *)0x55F8D0, arg0);
}
