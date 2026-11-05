/* 0x001552f0 — FUN_001552f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002e26b0();
int FUN_002e2bc0();
extern int DAT_004fb390[4];
void FUN_001552f0(int arg0) {
    FUN_002e2bc0();
    FUN_002e26b0(arg0, &DAT_004fb390[0]);
}
