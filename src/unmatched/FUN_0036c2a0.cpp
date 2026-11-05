/* 0x0036c2a0 — FUN_0036c2a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0036c4d0();
void FUN_0036c2a0(int arg0);
}

void FUN_0036c2a0(int arg0) {
    FUN_0036c4d0();
    igMetaObject_CreateInstance(*(int *)0x589E98, arg0);
}
