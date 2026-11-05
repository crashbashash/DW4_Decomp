/* 0x00134690 — FUN_00134690. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001347c0();
int igMetaObject_CreateInstance(int, int);

void FUN_00134690(int arg0) {
    FUN_001347c0();
    igMetaObject_CreateInstance(*(int *)0x55EF50, arg0);
}
