typedef struct N {
    long long f0;
    long long f8;
    char p16[8];
    struct N *f24;
    char p28[28];
    int f56;
    char p60[4];
    unsigned short f64;
    char p66[4];
    volatile char m : 7;
    char hi : 1;
    char p71;
    char f72;
} N;
typedef struct A {
    char p0[64];
    unsigned short f64;
    char p66[2];
    unsigned short f68;
} A;
extern N *DAT_0056c0d0[4];
extern N *DAT_0056c0d8[4];

N *FUN_0020b650(A *arg0, int *arg1, int arg2, long long *arg3) {
    N *sent;
    N *v;
    int pass;
    long long best;
    N *n;
    int lim;
    int a5;
    int mask;
    int base;

    sent = 0;
    v = DAT_0056c0d8[0];
    best = 0;
    pass = 0;
    while (pass < 2) {
        while (v != sent) {
            if (v->f72 == 0 && (v->m == 5 || v->m == 0 || (arg2 == 0 && v->m == 4))) {
                base = v->f56;
                a5 = base + v->f64;
                mask = arg0->f68;
                lim = (base + mask) & ~mask;
                n = v->f24;
                best = v->f8;
                while (((n != 0) ^ 1) == 0 && n->f72 == 0 && (n->m == 5 || n->m == 0 || (arg2 == 0 && n->m == 4)) && a5 < lim + arg0->f64) {
                    if (best < n->f8) {
                        best = n->f8;
                    }
                    a5 += n->f64;
                    n = n->f24;
                }
                if (a5 >= lim + arg0->f64) {
                    *arg1 = lim;
                    break;
                }
            }
            v = v->f24;
        }
        if (*arg1 != -1) {
            break;
        }
        pass++;
        v = DAT_0056c0d0[0];
        sent = DAT_0056c0d8[0];
    }
    if (arg3 != 0) {
        *arg3 = best;
    }
    return v;
}
