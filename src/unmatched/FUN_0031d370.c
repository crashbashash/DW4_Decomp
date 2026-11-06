int FUN_0031d370(void *arg0) {
    int temp_v1;
    int var_v0;

    temp_v1 = *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2028);
    var_v0 = temp_v1 >> 1;
    if (temp_v1 < 0) {
        var_v0 = (int) (temp_v1 + 1) >> 1;
    }
    return var_v0;
}
