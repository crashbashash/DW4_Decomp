typedef struct {
    int type;
    long long a;
    long long b;
} TimeQuery;
int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_001064c8(char *d, unsigned int cmd);
void FUN_001064f8(char *d);
void FUN_00109208(int sema, TimeQuery *q);

void FUN_0010a138(char *d, unsigned int cmd, unsigned int addr) {
    TimeQuery q;
    int intr;

    q.type = 2;
    FUN_00109208(*(int *)(d + 2160), &q);
    FUN_001064f8(d);
    *(volatile unsigned int *)0x10002000 = 0;
    FUN_001064f8(d);
    intr = FUN_00113f20();
    *(volatile unsigned int *)0x1000B410 = addr & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B420 = 4;
    *(volatile unsigned int *)0x1000B400 = 0x101;
    if (intr) {
        FUN_00113f78();
    }
    FUN_001064c8(d, cmd);
    FUN_001064f8(d);
    q.type = 3;
    FUN_00109208(*(int *)(d + 2160), &q);
}
