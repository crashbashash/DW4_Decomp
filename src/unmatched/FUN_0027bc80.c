/* 0x0027bc80 — FUN_0027bc80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004b5660[];
int memset();
extern int DAT_004b5668[4];
void FUN_0027bc80(void) {
    if (*(int *)DAT_004b5660 == 0) {
        memset(&DAT_004b5668[0], 0, 0x4000);
    }
    *(int *)DAT_004b5660 += 1;
}
