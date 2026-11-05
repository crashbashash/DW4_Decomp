/* 0x003624f0 — FUN_003624f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00362690();
void FUN_003624f0(int arg0);
}

void FUN_003624f0(int arg0) {
    FUN_00362690();
    igMetaObject_CreateInstance(*(int *)0x5896D8, arg0);
}
