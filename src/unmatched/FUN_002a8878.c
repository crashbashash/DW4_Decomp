typedef struct { char pad[56]; int f56; int f60; } Strm;
extern void FUN_002a0e70(int *c);
extern void FUN_002a0e88(int *c);
extern void FUN_002a8a30(void *h, Strm **a, Strm **b);
extern int FUN_002adc40(void *h, int k);
extern int FUN_002af6c0(void *h, int a, int b);
int FUN_002a8878(char *h) {
    int c;
    Strm *p, *q;
    int k, r;
    FUN_002a0e70(&c);
    FUN_002a8a30(h, &p, &q);
    if (*(int *)(h + 72) != 4) q = 0;
    k = FUN_002adc40(h, 15);
    if (p != 0 && (k == 0 || FUN_002af6c0(h, p->f56, p->f60) != 0)) {
        if (q != 0 && (k == 0 || FUN_002af6c0(h, q->f56, q->f60) != 0)) {
            r = 2;
        } else {
            r = 1;
        }
    } else {
        r = 0;
    }
    FUN_002a0e88(&c);
    return r;
}
