extern "C" {
/* 0x00335f70 — FUN_00335f70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00336090();

void FUN_00335f70(int arg0) {
    FUN_00336090();
    igMetaObject_CreateInstance(*(int *)0x587798, arg0);
}
}
