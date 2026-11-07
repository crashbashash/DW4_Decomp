extern void * DAT_005629f8[4];
int FUN_001d99d0(int *arg0, int *arg1) {
    int temp_a1;

    temp_a1 = *(int *)((char *)(DAT_005629f8[0]) + 16);
    return (int) (*(int *)((char *)((*(int *)(temp_a1 + (*arg0 * 4)))) + 20) - *(int *)((char *)((*(int *)(temp_a1 + (*arg1 * 4)))) + 20)) / 12;
}
