extern "C" {
/* 0x00336bd0 — FUN_00336bd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00336f10();

void FUN_00336bd0(int arg0) {
    FUN_00336f10();
    igMetaObject_CreateInstance(*(int *)0x587870, arg0);
}
}
