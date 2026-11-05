extern "C" {
/* 0x00348c70 — FUN_00348c70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00348e40();

void FUN_00348c70(int arg0) {
    FUN_00348e40();
    igMetaObject_CreateInstance(*(int *)0x588200, arg0);
}
}
