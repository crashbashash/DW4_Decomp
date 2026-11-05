/* 0x001f7470 — FUN_001f7470. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001f7470(int arg0) {
    *(int *)0x490D38 = arg0;
    *(int *)0x491478 = (int) (*(int *)0x491478 | 0x19);
}
