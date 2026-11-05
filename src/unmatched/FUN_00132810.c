/* 0x00132810 — FUN_00132810. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00132a00();
int igMetaObject_CreateInstance(int, int);

void FUN_00132810(int arg0) {
    FUN_00132a00();
    igMetaObject_CreateInstance(*(int *)0x55ED88, arg0);
}
