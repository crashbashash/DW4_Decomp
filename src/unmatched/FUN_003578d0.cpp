/* 0x003578d0 — FUN_003578d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00357d10();
void FUN_003578d0(int arg0);
}

void FUN_003578d0(int arg0) {
    FUN_00357d10();
    igMetaObject_CreateInstance(*(int *)0x588F38, arg0);
}
