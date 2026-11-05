/* 0x003bd0b0 — FUN_003bd0b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bd1d0();
void FUN_003bd0b0(int arg0);
}

void FUN_003bd0b0(int arg0) {
    FUN_003bd1d0();
    igMetaObject_CreateInstance(*(int *)0x58B188, arg0);
}
