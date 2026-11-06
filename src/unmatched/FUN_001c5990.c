int FUN_001c5990(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 8));
    return *(int *)(*(int *)((char *)(temp_v0) + 16) + ((*(int *)((char *)(temp_v0) + 8) - 1) * 4));
}
