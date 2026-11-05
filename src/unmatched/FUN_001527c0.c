/* 0x001527c0 — FUN_001527c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001528e0();
int igMetaObject_CreateInstance(int, int);

void FUN_001527c0(int arg0) {
    FUN_001528e0();
    igMetaObject_CreateInstance(*(int *)0x5604C0, arg0);
}
