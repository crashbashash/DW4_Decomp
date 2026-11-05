int FUN_001e99f0();

void FUN_00169c20(void *arg0, int arg1) {
    int var_a0;

    var_a0 = 0;
    if (arg1 & 1) {
        var_a0 |= 1;
    }
    if (arg1 & 2) {
        var_a0 |= 2;
    }
    FUN_001e99f0(var_a0, *(int *)((char *)(arg0) + 896), *(int *)((char *)(arg0) + 900));
}
