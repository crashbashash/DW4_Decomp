/* 0x001a3590 — FUN_001a3590. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001a3700();
int igMetaObject_CreateInstance(int, int);

void FUN_001a3590(int arg0) {
    FUN_001a3700();
    igMetaObject_CreateInstance(*(int *)0x561D30, arg0);
}
