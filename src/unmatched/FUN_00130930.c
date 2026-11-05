/* 0x00130930 — FUN_00130930. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00130a70();
int igMetaObject_CreateInstance(int, int);

void FUN_00130930(int arg0) {
    FUN_00130a70();
    igMetaObject_CreateInstance(*(int *)0x55EC28, arg0);
}
