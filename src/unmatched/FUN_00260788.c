/* 0x00260788 — FUN_00260788. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_00499cd8[4];
extern int DAT_00499cdc[4];
extern int DAT_00499ce0[4];
void FUN_00260788(void) {
    memset(&DAT_00499ce0[0], 0, 0x100);
    DAT_00499cd8[0] = 0;
    DAT_00499cdc[0] = 0;
}
