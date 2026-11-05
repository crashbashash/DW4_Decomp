/* 0x0020c880 — FUN_0020c880. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0020c880(int arg0) {
    if (arg0 > 0) {
        *(int *)0x56C128 = (int) (*(int *)0x56C128 | (1 << arg0));
    }
}
