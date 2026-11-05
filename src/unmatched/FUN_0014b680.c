/* 0x0014b680 — FUN_0014b680. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014b710();
int igMetaObject_CreateInstance(int, int);

void FUN_0014b680(int arg0) {
    FUN_0014b710();
    igMetaObject_CreateInstance(*(int *)0x55FA90, arg0);
}
