/* 0x00187560 — FUN_00187560. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00187680();
int igMetaObject_CreateInstance(int, int);

void FUN_00187560(int arg0) {
    FUN_00187680();
    igMetaObject_CreateInstance(*(int *)0x560F48, arg0);
}
