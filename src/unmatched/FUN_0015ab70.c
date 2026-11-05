/* 0x0015ab70 — FUN_0015ab70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memmove();

void FUN_0015ab70(int arg0, int arg1) {
    if (arg0 != arg1) {
        memmove();
    }
}
