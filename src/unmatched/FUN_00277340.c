extern char DAT_004abc70[];
int FUN_00277cd0();

void FUN_00277340(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)DAT_004abc70;
    var_s1 = 0x1F;
    do {
        if (*var_s0 == 1) {
            FUN_00277cd0(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x238;
    } while (var_s1 >= 0);
}
