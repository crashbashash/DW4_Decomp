/* 0x00279f68 — FUN_00279f68. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004b1df0[];
int FUN_00273820();
extern int DAT_004b1dc0[4];
extern int DAT_004b1dc8[4];
void FUN_00279f68(void) {
    if (((DAT_004b1dc8[0] != 1) || (DAT_004b1dc0[0] > 0)) && (*(int *)DAT_004b1df0 != 1)) {
        FUN_00273820(0xE, 0, 0, 0, 0);
        *(int *)DAT_004b1df0 = 1;
    }
}
