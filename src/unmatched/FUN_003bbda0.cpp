/* 0x003bbda0 — FUN_003bbda0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bbf60();
void FUN_003bbda0(int arg0);
}

void FUN_003bbda0(int arg0) {
    FUN_003bbf60();
    igMetaObject_CreateInstance(*(int *)0x58B060, arg0);
}
