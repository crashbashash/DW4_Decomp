/* 0x003b6bc0 — FUN_003b6bc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b6cf0();
void FUN_003b6bc0(int arg0);
}

void FUN_003b6bc0(int arg0) {
    FUN_003b6cf0();
    igMetaObject_CreateInstance(*(int *)0x58ACC8, arg0);
}
