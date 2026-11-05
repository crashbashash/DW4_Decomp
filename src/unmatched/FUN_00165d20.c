/* 0x00165d20 — FUN_00165d20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00165d20(int arg0) {
    *(int *)0x560780 = arg0;
}
