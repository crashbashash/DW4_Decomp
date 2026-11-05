/* 0x001284a8 — FUN_001284a8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00128470();
extern int DAT_004854a0[4];
void FUN_001284a8(int arg0) {
    FUN_00128470(DAT_004854a0[0], arg0);
}
