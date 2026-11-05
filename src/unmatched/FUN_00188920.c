/* 0x00188920 — FUN_00188920. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001889f0();
int igMetaObject_CreateInstance(int, int);

void FUN_00188920(int arg0) {
    FUN_001889f0();
    igMetaObject_CreateInstance(*(int *)0x561018, arg0);
}
