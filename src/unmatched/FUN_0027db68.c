/* 0x0027db68 — FUN_0027db68. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002737a8();
extern int DAT_004ba47c[4];
void FUN_0027db68(void) {
    int temp_v0;

    temp_v0 = DAT_004ba47c[0] - 1;
    DAT_004ba47c[0] = temp_v0;
    if (temp_v0 == 0) {
        FUN_002737a8();
    }
}
