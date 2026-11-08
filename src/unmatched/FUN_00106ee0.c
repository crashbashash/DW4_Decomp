typedef struct {
    int type;
    long long a;
    long long b;
} TimeQuery;
void FUN_00106df8(char *d);
unsigned int FUN_00106c88(char *d, int n);
void FUN_00107000(char *d);
void FUN_001074a0(char *d);
void FUN_00109208(int sema, TimeQuery *q);
void FUN_00109c88(char *d);
int FUN_00106ee0(char *d) {
    unsigned int code;
    TimeQuery q;

    for (;;) {
        if (*(int *)(d + 4256)) {
            return -1;
        }
        FUN_00106df8(d);
        code = FUN_00106c88(d, 32);
        switch (code) {
        case 0x1B3:
            FUN_00109c88(d);
            break;
        case 0x1B8:
            FUN_001074a0(d);
            break;
        case 0x100:
            FUN_00107000(d);
            q.type = 5;
            q.a = -1;
            q.b = -1;
            FUN_00109208(*(int *)(d + 2160), &q);
            *(long long *)(d + 2120) = q.b;
            *(long long *)(d + 2112) = q.a;
            return *(int *)(d + 360);
        case 0x1B7:
            return 0;
        }
    }
}
