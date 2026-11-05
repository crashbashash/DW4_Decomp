/* 0x00351420 — FUN_00351420. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003515b0();
void FUN_00351420(int arg0);
}

void FUN_00351420(int arg0) {
    FUN_003515b0();
    igMetaObject_CreateInstance(*(int *)0x588A20, arg0);
}
