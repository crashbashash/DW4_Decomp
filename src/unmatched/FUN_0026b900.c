/* 0x0026b900 — FUN_0026b900. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_0049c8f8[];
int FUN_0026b728();

void FUN_0026b900(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)DAT_0049c8f8;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            FUN_0026b728(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0xC4;
    } while (var_s1 >= 0);
}
