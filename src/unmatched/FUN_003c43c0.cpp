/* 0x003c43c0 — FUN_003c43c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c44e0();
void FUN_003c43c0(int arg0);
}

void FUN_003c43c0(int arg0) {
    FUN_003c44e0();
    igMetaObject_CreateInstance(*(int *)0x58BA30, arg0);
}
