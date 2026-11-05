extern "C" {
/* 0x00336200 — FUN_00336200. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_003364c0();

void FUN_00336200(int arg0) {
    FUN_003364c0();
    igMetaObject_CreateInstance(*(int *)0x5877B0, arg0);
}
}
