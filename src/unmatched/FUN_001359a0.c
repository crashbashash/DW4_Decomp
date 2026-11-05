/* 0x001359a0 — FUN_001359a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00135ac0();
int igMetaObject_CreateInstance(int, int);

void FUN_001359a0(int arg0) {
    FUN_00135ac0();
    igMetaObject_CreateInstance(*(int *)0x55F000, arg0);
}
