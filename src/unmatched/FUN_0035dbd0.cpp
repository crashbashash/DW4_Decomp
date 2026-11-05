/* 0x0035dbd0 — FUN_0035dbd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0035dd30();
void FUN_0035dbd0(int arg0);
}

void FUN_0035dbd0(int arg0) {
    FUN_0035dd30();
    igMetaObject_CreateInstance(*(int *)0x589380, arg0);
}
