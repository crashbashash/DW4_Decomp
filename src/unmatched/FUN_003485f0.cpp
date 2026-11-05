extern "C" {
/* 0x003485f0 — FUN_003485f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_003487c0();

void FUN_003485f0(int arg0) {
    FUN_003487c0();
    igMetaObject_CreateInstance(*(int *)0x5881E0, arg0);
}
}
