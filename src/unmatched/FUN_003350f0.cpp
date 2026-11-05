extern "C" {
/* 0x003350f0 — FUN_003350f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00335260();

void FUN_003350f0(int arg0) {
    FUN_00335260();
    igMetaObject_CreateInstance(*(int *)0x5876E0, arg0);
}
}
