/* 0x003b7c00 — FUN_003b7c00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b7d30();
void FUN_003b7c00(int arg0);
}

void FUN_003b7c00(int arg0) {
    FUN_003b7d30();
    igMetaObject_CreateInstance(*(int *)0x58AD88, arg0);
}
