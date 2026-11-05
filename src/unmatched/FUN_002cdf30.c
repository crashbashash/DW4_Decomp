/* 0x002cdf30 — FUN_002cdf30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ce050();
int igMetaObject_CreateInstance(int, int);

void FUN_002cdf30(int arg0) {
    FUN_002ce050();
    igMetaObject_CreateInstance(*(int *)0x586B20, arg0);
}
