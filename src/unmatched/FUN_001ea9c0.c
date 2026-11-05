struct E { char pad[8]; int f8; int f12; char pad2[24]; int f40; char pad3[20]; };
extern int DAT_00562d90[4];
extern struct E DAT_00562da0[4];
extern int DAT_00568da0[4];
void FUN_001ea9c0(int arg0) {
    int i;
    int n;
    int *sum;
    struct E *e;

    sum = &DAT_00562d90[arg0];
    *sum = 0;
    n = DAT_00568da0[0];
    for (i = 0; i <= n; i++) {
        e = &DAT_00562da0[i];
        if (arg0 == (e->f40 & 1)) {
            if (!(e->f40 & 4)) {
                e->f12 = e->f12 & ~1;
            } else {
                *sum += e->f8;
            }
        }
    }
}
