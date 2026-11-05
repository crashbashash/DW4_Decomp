/* 0x001361b0 — FUN_001361b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00136470();
int igMetaObject_CreateInstance(int, int);

void FUN_001361b0(int arg0) {
    FUN_00136470();
    igMetaObject_CreateInstance(*(int *)0x55F060, arg0);
}
