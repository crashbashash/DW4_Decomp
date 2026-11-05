/* 0x003b6310 — FUN_003b6310. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b64f0();
void FUN_003b6310(int arg0);
}

void FUN_003b6310(int arg0) {
    FUN_003b64f0();
    igMetaObject_CreateInstance(*(int *)0x58AC88, arg0);
}
