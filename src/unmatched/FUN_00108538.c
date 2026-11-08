typedef struct {
    int type;
    long long a;
    long long b;
} TimeQuery;
int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_001064c8(char *d, unsigned int cmd);
void FUN_00109208(int sema, TimeQuery *q);
void FUN_00108538(char *d, unsigned int addr, int n) {
    TimeQuery q;
    int intr;

    while (*(volatile int *)0x10002010 < 0);
    intr = FUN_00113f20();
    *(volatile unsigned int *)0x1000B010 = addr & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B020 = n << 6;
    *(volatile unsigned int *)0x1000B000 = 0x100;
    if (intr) {
        FUN_00113f78();
    }
    FUN_001064c8(d, n | 0x70000000);
    q.type = 4;
    FUN_00109208(*(int *)(d + 2160), &q);
    while ((*(volatile unsigned int *)0x1000B000 >> 8) & 1);
    while (*(volatile int *)0x10002010 < 0);
}
