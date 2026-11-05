extern "C" {
/* 0x0033f8b0 — FUN_0033f8b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_0033f9d0();

void FUN_0033f8b0(int arg0) {
    FUN_0033f9d0();
    igMetaObject_CreateInstance(*(int *)0x587A78, arg0);
}
}
