/* 0x00137070 — FUN_00137070. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00137140();
int igMetaObject_CreateInstance(int, int);

void FUN_00137070(int arg0) {
    FUN_00137140();
    igMetaObject_CreateInstance(*(int *)0x55F148, arg0);
}
