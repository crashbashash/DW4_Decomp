/* 0x0020ccd0 — FUN_0020ccd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0020cc50();
extern int DAT_0056c2a0[4];
void FUN_0020ccd0(void) {
    int temp_v1;

    temp_v1 = DAT_0056c2a0[0] - 1;
    DAT_0056c2a0[0] = temp_v1;
    if (temp_v1 == 0) {
        FUN_0020cc50();
    }
}
