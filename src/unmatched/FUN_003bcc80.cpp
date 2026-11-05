/* 0x003bcc80 — FUN_003bcc80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bcdd0();
void FUN_003bcc80(int arg0);
}

void FUN_003bcc80(int arg0) {
    FUN_003bcdd0();
    igMetaObject_CreateInstance(*(int *)0x58B160, arg0);
}
