int FUN_0015cfb0();

void FUN_001769f0(void *arg0) {
    int temp_a1;

    if (!(*(int *)((char *)(*(int *)((char *)(arg0) + 24)) + 20) & 0x10)) {
        FUN_0015cfb0();
        return;
    }
    temp_a1 = *(int *)((char *)(arg0) + 36);
    if (temp_a1 == 1) {
        FUN_0015cfb0(arg0, temp_a1);
    }
    *(char *)((char *)(arg0) + 32) = 0;
}
