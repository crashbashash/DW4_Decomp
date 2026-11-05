/* 0x00142f30 — FUN_00142f30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00143010();
int igMetaObject_CreateInstance(int, int);

void FUN_00142f30(int arg0) {
    FUN_00143010();
    igMetaObject_CreateInstance(*(int *)0x55F540, arg0);
}
