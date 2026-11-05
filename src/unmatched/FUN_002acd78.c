/* 0x002acd78 — FUN_002acd78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002aa538();
int FUN_002ada78();

void FUN_002acd78(int arg0) {
    if (FUN_002a0dd8() != 0) {
        FUN_002a0bb8(0, 0xFF000153, 1);
        return;
    }
    FUN_002ada78(arg0, 0x2F, 1);
    FUN_002aa538(arg0);
}
