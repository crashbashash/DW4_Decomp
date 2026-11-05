/* 0x0020cc10 — FUN_0020cc10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0020cd10();
extern int DAT_0056c2a0[4];
void FUN_0020cc10(void) {
    int temp_a0;

    temp_a0 = DAT_0056c2a0[0];
    DAT_0056c2a0[0] = temp_a0 + 1;
    if (temp_a0 == 0) {
        FUN_0020cd10();
    }
}
