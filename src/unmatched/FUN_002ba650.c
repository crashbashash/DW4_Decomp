/* 0x002ba650 — FUN_002ba650. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ba730();
int igMetaObject_CreateInstance(int, int);

void FUN_002ba650(int arg0) {
    FUN_002ba730();
    igMetaObject_CreateInstance(*(int *)0x585970, arg0);
}
