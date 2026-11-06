extern char DAT_004a5d70[];
int FUN_00269b90();

void FUN_00269bd0(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)DAT_004a5d70;
    var_s1 = 7;
    do {
        if (*var_s0 == 1) {
            FUN_00269b90(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x2F8;
    } while (var_s1 >= 0);
}
