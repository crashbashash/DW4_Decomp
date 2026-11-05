/* 0x00362f90 — FUN_00362f90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003630b0();
void FUN_00362f90(int arg0);
}

void FUN_00362f90(int arg0) {
    FUN_003630b0();
    igMetaObject_CreateInstance(*(int *)0x589780, arg0);
}
