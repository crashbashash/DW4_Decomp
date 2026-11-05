/* 0x00145d00 — FUN_00145d00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00145de0();
int igMetaObject_CreateInstance(int, int);

void FUN_00145d00(int arg0) {
    FUN_00145de0();
    igMetaObject_CreateInstance(*(int *)0x55F5D8, arg0);
}
