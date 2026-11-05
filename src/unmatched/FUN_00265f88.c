/* 0x00265f88 — FUN_00265f88. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_004a52d8[4];
void FUN_00265f88(void) {
    memset(&DAT_004a52d8[0], 0, 0xA80);
}
