/* 0x00130020 — FUN_00130020. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001301c0();
int igMetaObject_CreateInstance(int, int);

void FUN_00130020(int arg0) {
    FUN_001301c0();
    igMetaObject_CreateInstance(*(int *)0x55EBC0, arg0);
}
