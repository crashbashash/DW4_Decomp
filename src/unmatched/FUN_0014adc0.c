/* 0x0014adc0 — FUN_0014adc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014af80();
int igMetaObject_CreateInstance(int, int);

void FUN_0014adc0(int arg0) {
    FUN_0014af80();
    igMetaObject_CreateInstance(*(int *)0x55FA10, arg0);
}
