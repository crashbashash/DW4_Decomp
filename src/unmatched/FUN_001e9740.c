/* 0x001e9740 — FUN_001e9740. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001e9740(int arg0, int arg1) {
    *(int *)0x562D40 = arg0;
    *(int *)0x562D48 = arg1;
    *(int *)0x491478 = (int) (*(int *)0x491478 | 0xA0);
}
