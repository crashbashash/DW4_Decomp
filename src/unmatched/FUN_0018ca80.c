int FUN_0018ca80(void *arg0, void *arg1) {
    int var_v0;
    float temp_f8;
    float temp_f7;
    float temp_f6;
    float temp_f5;

    temp_f7 = *(float *)((char *)(arg0) + 12);
    temp_f6 = *(float *)((char *)(arg0) + 8);
    temp_f5 = *(float *)((char *)(arg0) + 16);
    temp_f8 = ((temp_f6 * *(float *)((char *)(arg1) + 8)) + (temp_f7 * *(float *)((char *)(arg1) + 12)) + (temp_f5 * *(float *)((char *)(arg1) + 16))) - *(float *)((char *)(arg0) + 20);
    if (temp_f8 <= 0.0f) {
        return 1;
    }
    var_v0 = 1;
    if (!((temp_f8 + (*(float *)((char *)(arg1) + 32) * ((temp_f6 * *(float *)((char *)(arg1) + 20)) + (temp_f7 * *(float *)((char *)(arg1) + 24)) + (temp_f5 * *(float *)((char *)(arg1) + 28))))) <= 0.0f)) {
        var_v0 = 0;
    }
    return var_v0;
}
