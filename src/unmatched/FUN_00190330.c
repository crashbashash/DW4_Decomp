/* 0x00190330 — FUN_00190330. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001902a0();

int FUN_00190330(int arg0, int arg1) {
    if (arg1 != arg0) {
        FUN_001902a0();
    }
    return arg0;
}
