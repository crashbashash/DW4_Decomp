/* 0x00459340 — FUN_00459340. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateInstance(int, int);
int FUN_00459e40();

void FUN_00459340(int arg0) {
    FUN_00459e40();
    igMetaObject_CreateInstance(*(int *)0x58C790, arg0);
}
