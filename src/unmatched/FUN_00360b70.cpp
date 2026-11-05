/* 0x00360b70 — FUN_00360b70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00360d30();
void FUN_00360b70(int arg0);
}

void FUN_00360b70(int arg0) {
    FUN_00360d30();
    igMetaObject_CreateInstance(*(int *)0x5895D0, arg0);
}
