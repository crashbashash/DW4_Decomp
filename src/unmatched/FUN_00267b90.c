/* 0x00267b90 — FUN_00267b90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_004a7530[4];
void FUN_00267b90(void) {
    memset(&DAT_004a7530[0], 0, 0xC0);
}
