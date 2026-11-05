extern "C" {
/* 0x00340cc0 — FUN_00340cc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00340e80();

void FUN_00340cc0(int arg0) {
    FUN_00340e80();
    igMetaObject_CreateInstance(*(int *)0x587BF8, arg0);
}
}
