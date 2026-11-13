void FUN_001064f8(char *d);
int _ipuShowBits(char *d, int n);
void _ipuFlushBits(char *d, int n);
void FUN_00106df8(char *d) {
    int n;

    FUN_001064f8(d);
    n = -(*(volatile int *)0x10002020 & 7) & 7;
    if (n != 0) {
        _ipuFlushBits(d, n);
    }
    while (_ipuShowBits(d, 24) != 1 && *(int *)(d + 4256) == 0) {
        _ipuFlushBits(d, 8);
    }
}
