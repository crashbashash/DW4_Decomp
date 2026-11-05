/* 0x00261d40 — FUN_00261d40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00499de8[];
int FUN_00261c88();

void FUN_00261d40(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)DAT_00499de8;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            FUN_00261c88(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x44;
    } while (var_s1 >= 0);
}
