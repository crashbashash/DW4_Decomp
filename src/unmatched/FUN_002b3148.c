void FUN_002b3148(void *arg0, unsigned char *arg1, unsigned char *arg2, unsigned char *arg3) {
    void *temp_a0;

    temp_a0 = (void *)((char *)arg0 + 0x14);
    *arg1 = *(int *)((char *)(arg0) + 20);
    *arg2 = *(int *)((char *)(temp_a0) + 1);
    *arg3 = *(int *)((char *)(temp_a0) + 2);
}
