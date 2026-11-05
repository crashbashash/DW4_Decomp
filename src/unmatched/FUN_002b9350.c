/* 0x002b9350 — FUN_002b9350. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b9470();
int igMetaObject_CreateInstance(int, int);

void FUN_002b9350(int arg0) {
    FUN_002b9470();
    igMetaObject_CreateInstance(*(int *)0x5858E8, arg0);
}
