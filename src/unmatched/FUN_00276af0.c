/* 0x00276af0 — FUN_00276af0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_004ab9f0[4];
void FUN_00276af0(void) {
    memset(&DAT_004ab9f0[0], 0, 0x10);
}
