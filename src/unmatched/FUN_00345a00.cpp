extern "C" {
/* 0x00345a00 — FUN_00345a00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00345bc0();

void FUN_00345a00(int arg0) {
    FUN_00345bc0();
    igMetaObject_CreateInstance(*(int *)0x587F98, arg0);
}
}
