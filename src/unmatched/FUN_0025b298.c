/* 0x0025b298 — FUN_0025b298. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_00498730[4];
extern int DAT_00498738[4];
void FUN_0025b298(void) {
    int temp_v0;

    temp_v0 = DAT_00498730[0] - 1;
    DAT_00498730[0] = temp_v0;
    if (temp_v0 == 0) {
        memset(&DAT_00498738[0], 0, 0x300);
    }
}
