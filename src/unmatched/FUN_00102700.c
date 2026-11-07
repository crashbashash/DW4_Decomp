typedef unsigned __int128 q128;
struct Ctx {
    char pad0[20]; int f20; char *f24; char pad1[256];
    q128 f288[14]; q128 f512; char pad2[16];
    unsigned int f544, f548; int f552; int pad3; int f560; unsigned int f564;
    char pad4[80]; int f648[32];
};
struct Arg { int a; char *f4; };
int FUN_00102700(struct Ctx *a, struct Arg *b) {
unsigned long long off;
int flag;
unsigned long long stop;
unsigned long long n;
int r;
q128 *qp;
int i;
unsigned long long cnt;
int *iw;
stop = a->f544;
off = a->f548;
flag = *b->f4 & 0x40;
n = a->f552;
    if (flag) {
        char *base;
        cnt = a->f564;
        base = a->f24 + (int)off;
        iw = (int *)(base + (int)((cnt * 4 + 15) & 0xFFFFFFFFFFFFFFF0ULL));
        qp = (q128 *)((unsigned long long)(unsigned int)iw + (n << 4));
    } else {
        qp = (q128 *)(a->f24 + (int)off + (int)(n << 4));
    }
    if (a->f560) qp++;
    r = *(int *)qp;
    if (a->f560) {
        qp--;
        a->f512 = *qp;
    } else if (n == 9) {
        qp--;
        n--;
        a->f512 = *qp;
    }
    qp -= (int)n;
    for (i = 0; (unsigned long long)i < n; i++) {
        a->f288[i] = *qp++;
    }
    a->f20 = (int)(a->f24 + (int)stop);
    if (flag) {
        iw -= (int)cnt;
        for (i = 0; (unsigned long long)i < cnt; i++) {
            a->f648[i] = *iw++;
        }
    }
    return r;
}
