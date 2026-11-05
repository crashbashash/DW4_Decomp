void FUN_0016e140(void *arg0, int arg1) {
    long long v;
    int temp_a2;
    void *temp_a1;
    int temp_v1;
    v = arg1;
    temp_a2 = *(int *)((char *)(arg0) + 60);
    temp_a1 = (void *)(*(int *)((char *)(arg0) + 56));
    temp_v1 = *(int *)((char *)(temp_a1) + 8);
    if ((temp_v1 != 0) && (temp_a2 >= 0) && (temp_a2 < temp_v1)) {
        *(long long *)(*(int *)((char *)(temp_a1) + 16) + (temp_a2 * 8)) = (long long)v;
    }
}
