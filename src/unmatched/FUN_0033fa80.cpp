extern "C" {
/* 0x0033fa80 — FUN_0033fa80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_0033fbf0();

void FUN_0033fa80(int arg0) {
    FUN_0033fbf0();
    igMetaObject_CreateInstance(*(int *)0x587A80, arg0);
}
}
