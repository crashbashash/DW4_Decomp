void FUN_002e24e0(void *arg0, int arg1, int arg2) {
    int temp_a4;
    int idx;
    char *p;
    if (arg1 < 0x10) {
        temp_a4 = 3 << (arg1 * 2);
        *(int *)((char *)(arg0) + 80) = (int)((int) (temp_a4 | (*(int *)((char *)(arg0) + 80) & ~temp_a4)));
        idx = arg1 * 4;
        p = (char *)(idx + (int)arg0);
        *(int *)(p + 84) = arg2;
    }
}
