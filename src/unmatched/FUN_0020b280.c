#include "dw4/ipa/ipa_FUN_002082b0.h"
typedef struct N {
    long long f0;
    long long f8;
    char p16[8];
    struct N *f24;
    struct N *f28;
    char p32[24];
    int f56;
    char p60[4];
    unsigned short f64;
    char p66[4];
    char m : 7;
    char hi : 1;
} N;
struct N *FUN_00208210();
extern N *DAT_0056c0d0[4];

void FUN_0020b280(N *arg0, N *arg1, int arg2) {
    long long var_s5;
    unsigned short a0;
    int x;
    N *s4;
    int s3;
    N *v0;
    int var_s4;
    N *s3n;
    long long old;
    int a0b;
    var_s5 = arg1->m;
    while (arg2 != arg1->f56) {
        a0 = arg1->f64;
        s4 = arg1->f28;
        s3 = arg2 >= arg1->f56 + a0;
        if (s4 != 0 && s4->m == 0) {
            if (s3 != 0) {
                s4->f64 += a0;
            } else {
                s4->f64 += ((arg2 - arg1->f56) & 0xFFFF);
            }
        } else {
            v0 = FUN_00208210();
            v0->f56 = arg1->f56;
            v0->f24 = arg1;
            v0->f28 = arg1->f28;
            arg1->f28 = v0;
            if (s4 != 0) {
                s4->f24 = v0;
            } else {
                DAT_0056c0d0[0] = v0;
            }
            if (s3 != 0) {
                v0->f64 = arg1->f64;
            } else {
                { int d = arg2 - arg1->f56; v0->f64 = d; }
            }
        }
        if (s3 != 0) {
            N *t1 = arg1->f28;
            N *a3 = arg1->f24;
            if (t1 != 0) {
                t1->f24 = a3;
            }
            if (a3 != 0) {
                a3->f28 = arg1->f28;
            }
            arg1->f24 = 0;
            arg1->f28 = 0;
            old = arg1->m;
            arg1->m = 1;
            arg1->f56 = -1;
            if (var_s5 == 0) {
                FUN_002082b0((O *)arg1);
            } else {
                arg1->hi = 1;
            }
            arg1 = a3;
            var_s5 = a3->m;
        } else {
            arg1->f64 -= ((arg2 - arg1->f56) & 0xFFFF);
            arg1->f56 = arg2;
        }
    }
    var_s4 = arg1->f64;
    goto reload;
    while (((s3n != 0) ^ 1) == 0 && (arg2 + arg0->f64) > (arg1->f56 + var_s4)) {
        unsigned short t;
        old = s3n->m;
        t = s3n->f64;
        arg1->f24 = s3n->f24;
        var_s4 += t;
        if (s3n->f24 != 0) {
            s3n->f24->f28 = arg1;
        }
        s3n->f24 = 0;
        s3n->f28 = 0;
        s3n->m = 1;
        s3n->f56 = -1;
        if (old == 0) {
            FUN_002082b0((O *)s3n);
        } else {
            s3n->hi = 1;
        }
    reload:
        s3n = arg1->f24;
    }
    a0b = arg1->f56 + var_s4;
    x = arg2 + arg0->f64;
    if (x < a0b) {
        if (s3n != 0 && s3n->m == 0) {
            s3n->f64 += ((a0b - x) & 0xFFFF);
            s3n->f56 = arg2 + arg0->f64;
        } else {
            v0 = FUN_00208210();
            v0->f56 = arg2 + arg0->f64;
            { int d = var_s4 - arg0->f64; v0->f64 = d; }
            v0->f24 = s3n;
            v0->f28 = arg1;
            arg1->f24 = v0;
            if (s3n != 0) {
                s3n->f28 = v0;
            }
        }
    }
    arg0->f56 = arg2;
    arg0->f24 = arg1->f24;
    arg0->f28 = arg1->f28;
    if (arg1->f28 != 0) {
        arg1->f28->f24 = arg0;
    }
    if (arg1->f24 != 0) {
        arg1->f24->f28 = arg0;
    }
    if (DAT_0056c0d0[0] == arg1) {
        DAT_0056c0d0[0] = arg0;
    }
    old = arg1->m;
    arg1->f24 = 0;
    arg1->f28 = 0;
    arg1->m = 1;
    arg1->f56 = -1;
    if (old == 0) {
        FUN_002082b0((O *)arg1);
        return;
    }
    arg1->hi = 1;
}
