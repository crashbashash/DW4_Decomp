/* 0x00189e40 — FUN_00189e40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00189f10();
int igMetaObject_CreateInstance(int, int);

void FUN_00189e40(int arg0) {
    FUN_00189f10();
    igMetaObject_CreateInstance(*(int *)0x561098, arg0);
}
