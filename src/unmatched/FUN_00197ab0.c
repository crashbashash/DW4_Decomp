/* 0x00197ab0 — FUN_00197ab0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00197cc0();
int igMetaObject_CreateInstance(int, int);

void FUN_00197ab0(int arg0) {
    FUN_00197cc0();
    igMetaObject_CreateInstance(*(int *)0x561450, arg0);
}
