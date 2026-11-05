/* 0x003cae00 — FUN_003cae00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003cb020();

void FUN_003cae00(int arg0) {
    FUN_003cb020();
    igMetaObject_CreateInstance(*(int *)0x58C158, arg0);
}
} /* extern "C" */
