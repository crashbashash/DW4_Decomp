int FUN_0022ac00(void *arg0) {
    int temp_v1;
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 12));
    temp_v1 = *(int *)((char *)(temp_v0) + 8);
    if (temp_v1 == 0) {
        return 0;
    }
    return *(int *)(*(int *)((char *)(temp_v0) + 16) + ((temp_v1 - 1) * 4));
}
