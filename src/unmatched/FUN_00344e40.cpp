extern "C" {
/* 0x00344e40 — FUN_00344e40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00345010();

void FUN_00344e40(int arg0) {
    FUN_00345010();
    igMetaObject_CreateInstance(*(int *)0x587F10, arg0);
}
}
