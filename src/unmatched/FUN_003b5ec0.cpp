/* 0x003b5ec0 — FUN_003b5ec0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b6110();
void FUN_003b5ec0(int arg0);
}

void FUN_003b5ec0(int arg0) {
    FUN_003b6110();
    igMetaObject_CreateInstance(*(int *)0x58AC48, arg0);
}
