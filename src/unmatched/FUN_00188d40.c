/* 0x00188d40 — FUN_00188d40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00188e10();
int igMetaObject_CreateInstance(int, int);

void FUN_00188d40(int arg0) {
    FUN_00188e10();
    igMetaObject_CreateInstance(*(int *)0x561030, arg0);
}
