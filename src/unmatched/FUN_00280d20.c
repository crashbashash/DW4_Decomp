/* 0x00280d20 — FUN_00280d20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004bb104[4];
int FUN_00280d20(void) {
    int var_a0;

    var_a0 = -1;
    if (DAT_004bb104[0] != 0) {
        DAT_004bb104[0] = 0;
        var_a0 = 0;
    }
    return var_a0;
}
