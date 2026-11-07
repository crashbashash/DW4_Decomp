int FUN_0018c990(void *arg0, void *arg1) {
    float temp_f7;
    int var_v0;

    temp_f7 = *(float *)((char *)(arg1) + 20);
    if (temp_f7 < 0.0f) {
        return 0;
    }
    var_v0 = 1;
    if (!((((*(float *)((char *)(arg0) + 8) * *(float *)((char *)(arg1) + 8)) + (*(float *)((char *)(arg0) + 12) * *(float *)((char *)(arg1) + 12)) + (*(float *)((char *)(arg0) + 16) * *(float *)((char *)(arg1) + 16))) - *(float *)((char *)(arg0) + 20)) <= temp_f7)) {
        var_v0 = 0;
    }
    return var_v0;
}
