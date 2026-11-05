/* 0x0025b248 — FUN_0025b248. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00498730[];
int memset();
extern int DAT_00498738[4];
void FUN_0025b248(void) {
    if (*(int *)DAT_00498730 == 0) {
        memset(&DAT_00498738[0], 0, 0x300);
    }
    *(int *)DAT_00498730 += 1;
}
