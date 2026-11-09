typedef struct S { char pad8[8]; int f8; int fC; unsigned int f10; } S;
int FUN_00229700();
int FUN_00229710();
int FUN_002297f0();
unsigned int FUN_00300e50();
int Gap__Core__igObject__vfunc_02();

void Gap__igItemDataBaseList__vfunc_04(S *arg0) {
    int n;
    int q;
    int neg;
    int cap;
    unsigned int p;
    unsigned int e;
    unsigned int q2;
    int r;

    n = arg0->f8;
    if (!(0 > arg0->fC)) {
        arg0->f8 = 0;
    } else {
        int c = *(const int *)&arg0->f8;
        neg = -c;
        if (c == 0) {
            cap = 0x400;
        } else {
            q = neg >> 0xA;
            if (neg < 0) {
                q = (neg + 0x3FF) >> 0xA;
            }
            cap = (q != 0) ? c + ((q + 1) << 0xA) : c * 2;
        }
        arg0->f10 = FUN_00300e50(arg0, arg0->f10, cap * 0xC);
        arg0->fC = cap;
        arg0->f8 = 0;
    }
    p = arg0->f10;
    e = p + (n * 0xC);
    q2 = e;
    while (q2 < p) {
        r = FUN_00229700(0xC, q2);
        if (r != 0) {
            FUN_00229710(r);
        }
        q2 += 0xC;
    }
    while (p < e) {
        FUN_002297f0(p, -1);
        p += 0xC;
    }
    Gap__Core__igObject__vfunc_02(arg0);
}
