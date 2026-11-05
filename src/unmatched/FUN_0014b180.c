/* 0x0014b180 — FUN_0014b180. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014b2a0();
int igMetaObject_CreateInstance(int, int);

void FUN_0014b180(int arg0) {
    FUN_0014b2a0();
    igMetaObject_CreateInstance(*(int *)0x55FA48, arg0);
}
