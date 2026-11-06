void FUN_0018fbc0(void *arg0, void *arg1, int arg2) {
    int temp_v1;
    int var_a0;
    unsigned int temp_a0;
    unsigned int temp_a3;
    void *temp_a1;

    temp_a3 = *(int *)((char *)arg0 + 8);
    temp_a0 = *(int *)((char *)arg1 + 8);
    if (temp_a3 < temp_a0) {
        var_a0 = (temp_a0 * (temp_a0 + 2)) - temp_a3;
    } else {
        var_a0 = temp_a0 + (temp_a3 * temp_a3);
    }
    temp_a1 = *(void **)0x561118;
    temp_v1 = *(int *)((char *)temp_a1 + 8);
    if ((temp_v1 != 0) && (var_a0 >= 0) && (var_a0 < temp_v1)) {
        *(int *)(*(int *)((char *)temp_a1 + 16) + (var_a0 * 4)) = arg2;
    }
}
