int FUN_00302780();

void Gap__Core__igObjectRefArrayMetaField__vfunc_37(void *arg0, int arg1, int arg2) {
    int var_s0;

    for (var_s0 = 0; var_s0 < *(int *)((char *)(arg0) + 68); var_s0++) {
        FUN_00302780(arg0, arg1, var_s0, *(int *)(arg2 + *(int *)((char *)(arg0) + 8) + (var_s0 * 4)));
    }
}
