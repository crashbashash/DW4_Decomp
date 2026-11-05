/* 0x00349af0 — FUN_00349af0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00349cc0();
void FUN_00349af0(int arg0);
}

void FUN_00349af0(int arg0) {
    FUN_00349cc0();
    igMetaObject_CreateInstance(*(int *)0x588278, arg0);
}
