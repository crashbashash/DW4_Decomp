/* 0x00150060 — FUN_00150060. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00150200();
int igMetaObject_CreateInstance(int, int);

void FUN_00150060(int arg0) {
    FUN_00150200();
    igMetaObject_CreateInstance(*(int *)0x55FF10, arg0);
}
