int FUN_002aa9c0(void *arg0) {
    int temp_v1;
    int var_a1;

    temp_v1 = *(int *)((char *)(arg0) + 76);
    var_a1 = *(int *)((char *)(arg0) + 72);
    if ((temp_v1 >= 2) && ((temp_v1 < 5) || (temp_v1 == 6))) {
        var_a1 = 2;
    }
    return var_a1;
}
