/* 0x0027eca8 — FUN_0027eca8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027e1c0();
int FUN_0027e1d8();
extern int (*DAT_00570bb8)();

int FUN_0027eca8(int *arg0) {
    int temp_v0;
    int var_s0;

    if (DAT_00570bb8 != 0) {
        var_s0 = (int)(DAT_00570bb8());
    } else {
        FUN_0027e1c0();
        temp_v0 = *arg0;
        *arg0 = 1;
        var_s0 = temp_v0 != 1;
        FUN_0027e1d8();
    }
    return var_s0;
}
