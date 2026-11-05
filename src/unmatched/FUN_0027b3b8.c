/* 0x0027b3b8 — FUN_0027b3b8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_004b5178[4];
extern int DAT_004b5180[4];
void FUN_0027b3b8(void) {
    int temp_v0;

    temp_v0 = DAT_004b5178[0] - 1;
    DAT_004b5178[0] = temp_v0;
    if (temp_v0 == 0) {
        memset(&DAT_004b5180[0], 0, 0x480);
    }
}
