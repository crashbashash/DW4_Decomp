extern "C" {
/* 0x003447c0 — FUN_003447c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00344890();

void FUN_003447c0(int arg0) {
    FUN_00344890();
    igMetaObject_CreateInstance(*(int *)0x587ED0, arg0);
}
}
