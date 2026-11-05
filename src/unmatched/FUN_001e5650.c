/* 0x001e5650 — FUN_001e5650. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001e5810();
int igMetaObject_CreateInstance(int, int);

void FUN_001e5650(int arg0) {
    FUN_001e5810();
    igMetaObject_CreateInstance(*(int *)0x562C10, arg0);
}
