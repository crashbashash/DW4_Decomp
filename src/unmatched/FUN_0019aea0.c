/* 0x0019aea0 — FUN_0019aea0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019b270();
int igMetaObject_CreateInstance(int, int);

void FUN_0019aea0(int arg0) {
    FUN_0019b270();
    igMetaObject_CreateInstance(*(int *)0x5615E0, arg0);
}
