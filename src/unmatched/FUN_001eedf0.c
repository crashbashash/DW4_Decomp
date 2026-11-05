typedef struct N { char pad0[12]; int f12; int f16; struct N *f20; } N;
int FUN_001eedf0(N *arg0) {
    int sz = arg0->f16 - arg0->f12;
    while ((arg0 = arg0->f20) != 0) {
        sz = sz - 16 + (arg0->f16 - arg0->f12);
    }
    return sz;
}
