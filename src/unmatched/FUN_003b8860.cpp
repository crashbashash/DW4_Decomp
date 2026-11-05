/* 0x003b8860 — FUN_003b8860. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b8a00();
void FUN_003b8860(int arg0);
}

void FUN_003b8860(int arg0) {
    FUN_003b8a00();
    igMetaObject_CreateInstance(*(int *)0x58AE08, arg0);
}
