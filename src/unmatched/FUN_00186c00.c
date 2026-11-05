/* 0x00186c00 — FUN_00186c00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00186d20();
int igMetaObject_CreateInstance(int, int);

void FUN_00186c00(int arg0) {
    FUN_00186d20();
    igMetaObject_CreateInstance(*(int *)0x560F10, arg0);
}
