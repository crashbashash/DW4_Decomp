/* 0x003c27c0 — FUN_003c27c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c28e0();
void FUN_003c27c0(int arg0);
}

void FUN_003c27c0(int arg0) {
    FUN_003c28e0();
    igMetaObject_CreateInstance(*(int *)0x58B5D8, arg0);
}
