/* 0x00267058 — FUN_00267058. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004a52d8[];
int FUN_00266d20();

void FUN_00267058(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)DAT_004a52d8;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            FUN_00266d20(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0xA8;
    } while (var_s1 >= 0);
}
