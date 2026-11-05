/* 0x0027b340 — FUN_0027b340. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004b5178[];
int memset();
extern int DAT_004b5180[4];
void FUN_0027b340(void) {
    if (*(int *)DAT_004b5178 == 0) {
        memset(&DAT_004b5180[0], 0, 0x480);
    }
    *(int *)DAT_004b5178 += 1;
}
