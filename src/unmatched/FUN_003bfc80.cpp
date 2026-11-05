/* 0x003bfc80 — FUN_003bfc80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c0280();
void FUN_003bfc80(int arg0);
}

void FUN_003bfc80(int arg0) {
    FUN_003c0280();
    igMetaObject_CreateInstance(*(int *)0x58B3C8, arg0);
}
