/* 0x001317c0 — FUN_001317c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001318f0();
int igMetaObject_CreateInstance(int, int);

void FUN_001317c0(int arg0) {
    FUN_001318f0();
    igMetaObject_CreateInstance(*(int *)0x55ECD8, arg0);
}
