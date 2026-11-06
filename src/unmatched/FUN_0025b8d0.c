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
