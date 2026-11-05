/* 0x0034f6f0 — FUN_0034f6f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0034f7c0();
void FUN_0034f6f0(int arg0);
}

void FUN_0034f6f0(int arg0) {
    FUN_0034f7c0();
    igMetaObject_CreateInstance(*(int *)0x5887C8, arg0);
}
