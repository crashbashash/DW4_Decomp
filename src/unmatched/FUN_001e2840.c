int FUN_001e2840(void *arg0) {
    int var_v0;
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 28));
    if (temp_v0 != 0) {
        var_v0 = *(int *)((char *)(temp_v0) + 8);
    } else {
        var_v0 = 0;
    }
    return var_v0 > 0;
}
