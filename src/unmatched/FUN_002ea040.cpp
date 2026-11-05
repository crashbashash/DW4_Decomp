class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(void *); };
extern "C" {
VC *FUN_002d7e90(void *, int);
extern int DAT_004fb410[4];
struct S { char pad8[8]; int cnt; char pad[244]; int f100; char pad2[8]; int f10c; int f110; };
void FUN_002ea040(int *arg0, S *arg1) {
    int i;
    int n;
    arg1->f100 = 0;
    arg1->f10c = 0;
    arg1->f110 = 0;
    n = arg1->cnt;
    for (i = 0; i < n; i++) {
        FUN_002d7e90(arg1, i)->vX(arg1);
    }
    *arg0 = DAT_004fb410[0];
}
}
