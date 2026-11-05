/* 0x0028ea10 — FUN_0028ea10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0028ea30();
extern int DAT_004bccb8[4];
void FUN_0028ea10(void) {
    FUN_0028ea30(&DAT_004bccb8[0]);
}
