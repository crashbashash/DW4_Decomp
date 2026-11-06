void FUN_002b3110(void *arg0, int *arg1, int *arg2, int *arg3) {
    void *temp_a0;

    temp_a0 = (void *)((char *)arg0 + 8);
    *arg3 = *(int *)((char *)(arg0) + 8);
    *arg1 = *(int *)((char *)(temp_a0) + 4);
    *arg2 = *(int *)((char *)(temp_a0) + 8);
}
