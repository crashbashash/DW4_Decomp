/* 0x003694a0 — FUN_003694a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00369600();
void FUN_003694a0(int arg0);
}

void FUN_003694a0(int arg0) {
    FUN_00369600();
    igMetaObject_CreateInstance(*(int *)0x589C38, arg0);
}
