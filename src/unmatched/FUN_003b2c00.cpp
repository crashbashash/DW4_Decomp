/* 0x003b2c00 — FUN_003b2c00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b30f0();
void FUN_003b2c00(int arg0);
}

void FUN_003b2c00(int arg0) {
    FUN_003b30f0();
    igMetaObject_CreateInstance(*(int *)0x58AB38, arg0);
}
