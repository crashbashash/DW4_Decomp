/* 0x003c2e60 — FUN_003c2e60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c2f80();
void FUN_003c2e60(int arg0);
}

void FUN_003c2e60(int arg0) {
    FUN_003c2f80();
    igMetaObject_CreateInstance(*(int *)0x58B740, arg0);
}
