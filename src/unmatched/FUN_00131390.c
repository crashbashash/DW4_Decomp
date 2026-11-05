/* 0x00131390 — FUN_00131390. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001314b0();
int igMetaObject_CreateInstance(int, int);

void FUN_00131390(int arg0) {
    FUN_001314b0();
    igMetaObject_CreateInstance(*(int *)0x55ECA8, arg0);
}
