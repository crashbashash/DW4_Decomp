/* 0x00296438 — FUN_00296438. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00294308();
int FUN_002964a0();
int FUN_002968c0();
int FUN_0029a320();
extern int DAT_004f3a48[4];
int FUN_00296438(int arg0) {
    int temp_s0;

    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f3a48[0]);
        return 0;
    }
    temp_s0 = FUN_002964a0(arg0);
    return temp_s0 + FUN_00294308(arg0);
}
