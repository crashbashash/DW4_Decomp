/* 0x00369820 — FUN_00369820. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00369a20();
void FUN_00369820(int arg0);
}

void FUN_00369820(int arg0) {
    FUN_00369a20();
    igMetaObject_CreateInstance(*(int *)0x589C90, arg0);
}
