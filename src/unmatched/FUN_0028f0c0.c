void FUN_0028f0c0(void *arg0, int arg1, int arg2) {
    void *temp_a0;

    temp_a0 = (void *)((char *)arg0 + 0x3E8);
    *(int *)((char *)(arg0) + 1000) = arg1;
    *(int *)((char *)(temp_a0) + 4) = arg2;
    *(int *)((char *)(temp_a0) + 8) = 0;
}
