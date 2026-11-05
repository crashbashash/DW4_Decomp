extern "C" {
/* 0x003442b0 — FUN_003442b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_003444c0();

void FUN_003442b0(int arg0) {
    FUN_003444c0();
    igMetaObject_CreateInstance(*(int *)0x587EA8, arg0);
}
}
