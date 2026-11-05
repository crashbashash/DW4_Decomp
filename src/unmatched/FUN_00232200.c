/* 0x00232200 — FUN_00232200. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00232320();
int igMetaObject_CreateInstance(int, int);

void FUN_00232200(int arg0) {
    FUN_00232320();
    igMetaObject_CreateInstance(*(int *)0x56DB30, arg0);
}
