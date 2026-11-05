int FUN_0030d1d0();

int FUN_002e14b0(void *arg0, int arg1) {
    int temp_a1;
    int idx;

    if (arg1 >= 0 && arg1 < 0x20) {
        idx = arg1 * 4;
        temp_a1 = *(int *)((char *)(idx + (int)arg0) + 96);
        if (temp_a1 != -1) {
            return FUN_0030d1d0(*(int *)((char *)(arg0) + 48), temp_a1);
        }
    }
    return 0;
}
