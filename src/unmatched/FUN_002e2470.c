void FUN_002e2470(void *arg0, int arg1, int arg2) {
    int temp_a5;

    if (arg1 < 0x10) {
        temp_a5 = arg1 * 2;
        *(int *)((char *)(arg0) + 80) = (int)((int) ((2 << temp_a5) | (*(int *)((char *)(arg0) + 80) & ~(3 << temp_a5))));
        *(int *)((arg1 << 2) + (int)arg0 + 84) = arg2;
    }
}
