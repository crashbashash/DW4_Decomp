/* 0x003bf1b0 — FUN_003bf1b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bf3f0();
void FUN_003bf1b0(int arg0);
}

void FUN_003bf1b0(int arg0) {
    FUN_003bf3f0();
    igMetaObject_CreateInstance(*(int *)0x58B368, arg0);
}
