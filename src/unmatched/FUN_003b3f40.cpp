/* 0x003b3f40 — FUN_003b3f40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b4190();
void FUN_003b3f40(int arg0);
}

void FUN_003b3f40(int arg0) {
    FUN_003b4190();
    igMetaObject_CreateInstance(*(int *)0x58AB80, arg0);
}
