/* 0x003bdb10 — FUN_003bdb10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bdf00();
void FUN_003bdb10(int arg0);
}

void FUN_003bdb10(int arg0) {
    FUN_003bdf00();
    igMetaObject_CreateInstance(*(int *)0x58B200, arg0);
}
