/* 0x003bd3f0 — FUN_003bd3f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bd540();
void FUN_003bd3f0(int arg0);
}

void FUN_003bd3f0(int arg0) {
    FUN_003bd540();
    igMetaObject_CreateInstance(*(int *)0x58B1D8, arg0);
}
