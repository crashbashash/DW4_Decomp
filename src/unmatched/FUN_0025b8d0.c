/* 0x0025b8d0 — FUN_0025b8d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00498738[];
int FUN_0025b8a8();

void FUN_0025b8d0(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)DAT_00498738;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            FUN_0025b8a8(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x30;
    } while (var_s1 >= 0);
}
