/* 0x00133160 — FUN_00133160. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00133290();
int igMetaObject_CreateInstance(int, int);

void FUN_00133160(int arg0) {
    FUN_00133290();
    igMetaObject_CreateInstance(*(int *)0x55EE28, arg0);
}
