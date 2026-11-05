int FUN_00307750();
struct M { char pad[12]; int f12; };
struct M *FUN_00307c10();
int FUN_0030b670();
unsigned char FUN_00306e50(int arg0, int arg1, int arg2, char *arg3, int arg4, int arg5) {
    unsigned char var_s0;
    struct M *temp_v0;

    var_s0 = 0;
    temp_v0 = FUN_00307c10(arg0, arg1, arg2, 0);
    if ((temp_v0 != 0) && (FUN_0030b670(temp_v0->f12, arg3) != 0)) {
        var_s0 = 1;
    }
    if (!var_s0) {
        *arg3 = arg4;
        if (arg5 != 0) {
            FUN_00307750(arg0, arg1, arg2, arg4);
        }
    }
    return var_s0;
}
