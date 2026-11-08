int strcmp();
extern int DAT_004c22f0[4];
void FUN_001b7740(void **arg0, void **arg1) {
    int var_a0;
    int var_a1;

    var_a0 = *(int *)((char *)((*arg0)) + 8);
    if (var_a0 == 0) {
        var_a0 = DAT_004c22f0[0];
    }
    var_a1 = *(int *)((char *)((*arg1)) + 8);
    if (var_a1 == 0) {
        var_a1 = DAT_004c22f0[0];
    }
    strcmp(var_a0, var_a1);
}
