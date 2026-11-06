int FUN_0030d1d0();
int FUN_002e1500(void *arg0, int arg1) {
    int off;
    int temp_a1;

    if (arg1 >= 0 && arg1 < 0x20) {
        off = arg1 * 4;
        temp_a1 = *(int *)((char *)(off + (int)arg0) + 228);
        if (temp_a1 != -1) {
            return FUN_0030d1d0(*(int *)((char *)(arg0) + 48), temp_a1);
        }
    }
    return 0;
}
