extern "C" {
/* 0x0033f410 — FUN_0033f410. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_0033f750();

void FUN_0033f410(int arg0) {
    FUN_0033f750();
    igMetaObject_CreateInstance(*(int *)0x587A68, arg0);
}
}
