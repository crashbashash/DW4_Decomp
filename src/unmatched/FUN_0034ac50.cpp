/* 0x0034ac50 — FUN_0034ac50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0034ad70();
void FUN_0034ac50(int arg0);
}

void FUN_0034ac50(int arg0) {
    FUN_0034ad70();
    igMetaObject_CreateInstance(*(int *)0x5883A0, arg0);
}
