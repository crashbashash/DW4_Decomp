/* 0x003b8f50 — FUN_003b8f50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b9120();
void FUN_003b8f50(int arg0);
}

void FUN_003b8f50(int arg0) {
    FUN_003b9120();
    igMetaObject_CreateInstance(*(int *)0x58AE38, arg0);
}
