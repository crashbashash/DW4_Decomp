/* 0x002aa548 — FUN_002aa548. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029d0e0();
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002afb98();

int FUN_002aa548(int arg0, int arg1) {
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000144);
    }
    FUN_002afb98(arg0, arg1);
    FUN_0029d0e0(arg0, arg1);
    return 0;
}
