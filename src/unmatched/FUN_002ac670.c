/* 0x002ac670 — FUN_002ac670. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029dab8();
int FUN_002a0bb8();
int FUN_002a0dd8();

void FUN_002ac670(int arg0, int arg1) {
    if (FUN_002a0dd8() != 0) {
        FUN_002a0bb8(0, 0xFF000139);
        return;
    }
    FUN_0029dab8(arg0, arg1);
}
