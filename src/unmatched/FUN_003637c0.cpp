/* 0x003637c0 — FUN_003637c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363930();
void FUN_003637c0(int arg0);
}

void FUN_003637c0(int arg0) {
    FUN_00363930();
    igMetaObject_CreateInstance(*(int *)0x5897D8, arg0);
}
