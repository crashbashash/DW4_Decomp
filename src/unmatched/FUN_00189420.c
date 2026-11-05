/* 0x00189420 — FUN_00189420. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001894f0();
int igMetaObject_CreateInstance(int, int);

void FUN_00189420(int arg0) {
    FUN_001894f0();
    igMetaObject_CreateInstance(*(int *)0x561058, arg0);
}
