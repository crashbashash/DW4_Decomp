/* 0x002aa6c0 — FUN_002aa6c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();
extern int DAT_004f5020[4];
void FUN_002aa6c0(void) {
    if (DAT_004f5020[0] != 0x5A5A5A5A) {
        FUN_002a0bb8(0, 0xFF000201);
    }
}
