/* 0x00246760 — FUN_00246760. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00246760(int arg0, int arg1) {
    *(int *)0x56DF30 = arg0;
    *(int *)0x56DF38 = arg1;
}
