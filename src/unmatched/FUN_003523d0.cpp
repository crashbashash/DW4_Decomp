/* 0x003523d0 — FUN_003523d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003525e0();
void FUN_003523d0(int arg0);
}

void FUN_003523d0(int arg0) {
    FUN_003525e0();
    igMetaObject_CreateInstance(*(int *)0x588B00, arg0);
}
