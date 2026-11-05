extern "C" {
/* 0x00335b40 — FUN_00335b40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00335c10();

void FUN_00335b40(int arg0) {
    FUN_00335c10();
    igMetaObject_CreateInstance(*(int *)0x587760, arg0);
}
}
