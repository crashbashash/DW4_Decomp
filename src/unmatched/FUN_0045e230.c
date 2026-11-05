/* 0x0045e230 — FUN_0045e230. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_0045e4a0();

void FUN_0045e230(int arg0) {
    FUN_0045e4a0();
    igMetaObject_CreateInstance(*(int *)0x58CE60, arg0);
}
