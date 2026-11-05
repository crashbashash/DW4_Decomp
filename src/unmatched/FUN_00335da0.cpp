extern "C" {
/* 0x00335da0 — FUN_00335da0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00335ec0();

void FUN_00335da0(int arg0) {
    FUN_00335ec0();
    igMetaObject_CreateInstance(*(int *)0x587790, arg0);
}
}
