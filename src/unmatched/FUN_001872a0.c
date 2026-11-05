/* 0x001872a0 — FUN_001872a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001873c0();
int igMetaObject_CreateInstance(int, int);

void FUN_001872a0(int arg0) {
    FUN_001873c0();
    igMetaObject_CreateInstance(*(int *)0x560F38, arg0);
}
