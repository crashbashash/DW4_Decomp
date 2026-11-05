/* 0x00354a60 — FUN_00354a60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00354b80();
void FUN_00354a60(int arg0);
}

void FUN_00354a60(int arg0) {
    FUN_00354b80();
    igMetaObject_CreateInstance(*(int *)0x588D20, arg0);
}
