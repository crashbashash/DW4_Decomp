int FUN_0010e4a0(void *arg0) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(arg0) + 0));
    if ((temp_a1 == 0) || (*(int *)((char *)(arg0) + 4) != *(int *)((char *)(temp_a1) + 24)) || !(*(int *)((char *)(temp_a1) + 16) & 1)) {
        return 0;
    }
    return 1;
}
