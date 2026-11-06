int FUN_0026b348();
int FUN_0026cb98();
int FUN_0029c880();
int FUN_002abf68();

int FUN_0029c810(void *arg0) {
    int var_v0;
    int var_v0_2;

    if (FUN_002abf68() != 1) {
        var_v0_2 = FUN_0026b348(*(int *)((char *)(arg0) + 12), *(int *)((char *)(arg0) + 24), *(int *)((char *)(arg0) + 20));
    } else {
        var_v0_2 = FUN_0029c880();
    }
    var_v0 = 0;
    if (var_v0_2 != 0) {
        FUN_0026cb98(var_v0_2, 0);
        var_v0 = var_v0_2;
    }
    return var_v0;
}
