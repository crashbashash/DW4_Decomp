/* 0x002aa628 — FUN_002aa628. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002ad950();

int FUN_002aa628(int arg0, int arg1) {
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000146, arg1);
    }
    FUN_002ad950(arg0, 0x1D, arg1);
    return 0;
}
