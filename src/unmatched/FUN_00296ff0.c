int FUN_002a3200();

void FUN_00296ff0(void *arg0, int arg1) {
    int var_a0;

    var_a0 = 0;
    if (arg0 != 0) {
        var_a0 = *(int *)((char *)(arg0) + 64);
    }
    if (arg1 == 1) {
        FUN_002a3200(var_a0, 4, 1);
        return;
    }
    FUN_002a3200(var_a0, 4, 0);
}
