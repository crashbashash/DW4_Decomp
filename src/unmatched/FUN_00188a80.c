/* 0x00188a80 — FUN_00188a80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00188b50();
int igMetaObject_CreateInstance(int, int);

void FUN_00188a80(int arg0) {
    FUN_00188b50();
    igMetaObject_CreateInstance(*(int *)0x561020, arg0);
}
