/* 0x0013aec0 — FUN_0013aec0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0013afe0();
int igMetaObject_CreateInstance(int, int);

void FUN_0013aec0(int arg0) {
    FUN_0013afe0();
    igMetaObject_CreateInstance(*(int *)0x55F460, arg0);
}
