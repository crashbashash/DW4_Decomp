/* 0x00277f30 — FUN_00277f30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004b03e8[];
int FUN_00277f28();

void FUN_00277f30(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)DAT_004b03e8;
    var_s1 = 0x27;
    do {
        if (*var_s0 != 0) {
            FUN_00277f28(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x38;
    } while (var_s1 >= 0);
}
