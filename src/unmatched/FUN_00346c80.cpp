extern "C" {
/* 0x00346c80 — FUN_00346c80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00346ef0();

void FUN_00346c80(int arg0) {
    FUN_00346ef0();
    igMetaObject_CreateInstance(*(int *)0x588020, arg0);
}
}
