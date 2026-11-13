extern char DAT_004d1fd8[];
void FUN_00104258(char *d, int first);
int FUN_00105250(char *d);
int FUN_001059e8(char *d, int count);
void FUN_001064f8(char *d);
void _sceMpegMessage(char *d, const char *msg, ...);
int FUN_001057a0(char *d) {
    int count;
    int r;

    *(int *)(d + 2088) = 0;
    count = *(int *)(d + 324) * *(int *)(d + 328);
    *(int *)(d + 2092) = 0;
    if (*(int *)(d + 396) != 3) {
        count >>= 1;
    }
    do {
        r = FUN_001059e8(d, count);
    } while (r == 1 || r == 3);
    FUN_001064f8(d);
    if (!FUN_00105250(d)) {
        if (*(int *)(d + 4256)) {
            return 4;
        }
        r = 2;
    }
    while ((*(volatile unsigned int *)0x1000D400 >> 8) & 1);
    if (r == 0) {
        FUN_00104258(d, *(int *)(d + 2088) == 0);
    }
    if (r == 1 || r == 2) {
        _sceMpegMessage(d, DAT_004d1fd8);
    }
    return r == 0;
}
