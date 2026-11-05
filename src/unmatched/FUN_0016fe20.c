/* 0x0016fe20 — FUN_0016fe20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memmove();

void FUN_0016fe20(int arg0, int arg1) {
    if (arg0 != arg1) {
        memmove();
    }
}
