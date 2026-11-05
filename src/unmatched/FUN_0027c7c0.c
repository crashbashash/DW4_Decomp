/* 0x0027c7c0 — FUN_0027c7c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004b9698[];
int memset();
extern int DAT_004b96a0[4];
void FUN_0027c7c0(void) {
    if (*(int *)DAT_004b9698 == 0) {
        memset(&DAT_004b96a0[0], 0, 0xC00);
    }
    *(int *)DAT_004b9698 += 1;
}
