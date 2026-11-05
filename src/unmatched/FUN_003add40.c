extern int DAT_004c91f0[4];
extern int DAT_0058a800[4];
extern int DAT_0058a810[4];
extern char GPR_005549dc;
typedef struct L { char p8[8]; int n; int p12; int *d; } L;
typedef struct A { char p0[12]; L *l12; char p16[32]; L *l48; char p52[4]; L *l56; } A;
typedef struct B { int w[64]; } B;

int FUN_003add40(int *arg0, A *arg1) {
    L *a4;
    L *a3;
    L *a2;
    int i;
    int n;
    int *d;
    int *p;
    int cnt;
    int j;
    int c;
    int off;
    a4 = arg1->l12;
    a3 = arg1->l48;
    a2 = arg1->l56;
    cnt = 0;
    if (DAT_0058a800[0] == 0) {
        *(char *)((char *)arg1 + 40) = GPR_005549dc;
    }
    n = a4->n;
    d = a4->d;
    for (j = 0; j < n; j++) {
        d[j] = DAT_004c91f0[0];
    }
    i = 0;
    if (0 < a4->n) {
        off = 0;
        p = &DAT_0058a810[0];
        do {
            c = *(volatile int *)&a4->n;
            if (c != 0 && i >= 0 && i < c) {
                *(int *)((char *)a4->d + off) = *p;
            }
            if (*p == 1) {
                c = *(volatile int *)&a3->n;
                if (c != 0 && i >= 0 && i < c) {
                    *(int *)((char *)a3->d + off) = arg0[16];
                }
                c = *(volatile int *)&a2->n;
                if (c != 0 && i >= 0 && i < c) {
                    *(int *)((char *)a2->d + off) = arg0[24];
                }
                cnt++;
            }
            i++;
            p++;
            off += 4;
            arg0++;
        } while (i < a4->n);
    }
    return cnt;
}
