extern "C" {
int FUN_003076b0(int, int, int, float);
void *FUN_00307c10(int, int, int, int);
int FUN_0030b630(int, float *);

bool FUN_003066b0(int arg0, int arg1, int arg2, float *arg3, int arg4, float fparg0) {
    bool var_s0;
    void *temp_v0;

    var_s0 = false;
    temp_v0 = (void *)(FUN_00307c10(arg0, arg1, arg2, 0));
    if ((temp_v0 != 0) && (FUN_0030b630(*(int *)((char *)(temp_v0) + 12), arg3) != 0)) {
        var_s0 = true;
    }
    if (!var_s0) {
        *arg3 = fparg0;
        if (arg4 != 0) {
            FUN_003076b0(arg0, arg1, arg2, fparg0);
        }
    }
    return var_s0;
}
}
