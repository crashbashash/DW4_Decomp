void FUN_0015d6c0(void *arg0, int arg1, void *arg2) {
    int temp_a0;
    float *var_v1;
    float *src = (float *)arg2;
    temp_a0 = *(int *)((char *)(*(int *)((char *)(*(int *)((char *)(arg0) + 24)) + 8)) + 64);
    var_v1 = temp_a0 ? (float *)(temp_a0 + arg1 * 0xC) : 0;
    var_v1[0] = src[0];
    var_v1[1] = src[1];
    var_v1[2] = src[2];
}
