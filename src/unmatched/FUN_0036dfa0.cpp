/* 0x0036dfa0 — FUN_0036dfa0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0036e160();
void FUN_0036dfa0(int arg0);
}

void FUN_0036dfa0(int arg0) {
    FUN_0036e160();
    igMetaObject_CreateInstance(*(int *)0x58A030, arg0);
}
