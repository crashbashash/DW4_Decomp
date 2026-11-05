/* 0x003ba760 — FUN_003ba760. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003ba850();
void FUN_003ba760(int arg0);
}

void FUN_003ba760(int arg0) {
    FUN_003ba850();
    igMetaObject_CreateInstance(*(int *)0x58AF20, arg0);
}
