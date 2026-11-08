void FUN_001064f8(char *d);
int FUN_00106a58(char *d, int n);
void FUN_00106b78(char *d, int n);
void FUN_00106df8(char *d) {
    int n;

    FUN_001064f8(d);
    n = -(*(volatile int *)0x10002020 & 7) & 7;
    if (n != 0) {
        FUN_00106b78(d, n);
    }
    while (FUN_00106a58(d, 24) != 1 && *(int *)(d + 4256) == 0) {
        FUN_00106b78(d, 8);
    }
}
