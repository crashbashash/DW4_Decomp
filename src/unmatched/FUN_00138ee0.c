/* 0x00138ee0 — FUN_00138ee0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00139000();
int igMetaObject_CreateInstance(int, int);

void FUN_00138ee0(int arg0) {
    FUN_00139000();
    igMetaObject_CreateInstance(*(int *)0x55F2E0, arg0);
}
