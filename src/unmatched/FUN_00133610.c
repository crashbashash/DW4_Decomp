/* 0x00133610 — FUN_00133610. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001336e0();
int igMetaObject_CreateInstance(int, int);

void FUN_00133610(int arg0) {
    FUN_001336e0();
    igMetaObject_CreateInstance(*(int *)0x55EE50, arg0);
}
