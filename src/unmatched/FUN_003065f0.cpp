extern "C" {
int FUN_00307660(int, int, int, int);
void *FUN_00307c10(int, int, int, int);
int FUN_0030b5f0(int, int *);

bool FUN_003065f0(int arg0, int arg1, int arg2, int *arg3, int arg4, int arg5);
}
bool FUN_003065f0(int arg0, int arg1, int arg2, int *arg3, int arg4, int arg5) {
    bool var_s0;
    void *temp_v0;

    var_s0 = false;
    temp_v0 = FUN_00307c10(arg0, arg1, arg2, 0);
    if ((temp_v0 != 0) && (FUN_0030b5f0(*(int *)((char *)(temp_v0) + 12), arg3) != 0)) {
        var_s0 = true;
    }
    if (!var_s0) {
        *arg3 = arg4;
        if (arg5 != 0) {
            FUN_00307660(arg0, arg1, arg2, arg4);
        }
    }
    return var_s0;
}
