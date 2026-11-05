/* 0x002fe570 — FUN_002fe570. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_AddField();
int FUN_002fe5a0(int);

void FUN_002fe570(int arg0) {
    igMetaObject_AddField();
    FUN_002fe5a0(arg0);
}
