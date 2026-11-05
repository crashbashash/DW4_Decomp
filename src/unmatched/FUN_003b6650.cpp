/* 0x003b6650 — FUN_003b6650. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b67e0();
void FUN_003b6650(int arg0);
}

void FUN_003b6650(int arg0) {
    FUN_003b67e0();
    igMetaObject_CreateInstance(*(int *)0x58ACA8, arg0);
}
