class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void vX(int); };
struct O { int p0; int p1; int n; char pad[44]; unsigned char f56; };
extern "C" {
E *FUN_002d7e90(O *, int);
extern int DAT_004fb410[4];
}
extern "C" void FUN_002e94b0(int *arg0, O *arg1) {
    int i;
    int n;
    int flag;
    E *e;
    i = 0;
    n = arg1->n;
    flag = !arg1->f56;
    while (i < n) {
        e = FUN_002d7e90(arg1, i);
        e->vX(flag);
        i += 1;
    }
    if (flag != 0) {
        arg1->f56 = 1;
    }
    *arg0 = DAT_004fb410[0];
}
