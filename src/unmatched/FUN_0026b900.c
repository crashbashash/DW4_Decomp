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
