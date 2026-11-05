/* 0x003b9db0 — FUN_003b9db0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b9ed0();
void FUN_003b9db0(int arg0);
}

void FUN_003b9db0(int arg0) {
    FUN_003b9ed0();
    igMetaObject_CreateInstance(*(int *)0x58AEF8, arg0);
}
