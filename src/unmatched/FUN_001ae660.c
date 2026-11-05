int FUN_001adec0();
struct L { char p0[8]; int count; char p1[4]; int items; };
struct O { char p0[56]; struct L *list; };
struct E { char p0[72]; long long f72; float f80; float f84; long long f88; long long f96; };
int FUN_001ae660(struct O *arg0, int a1, int a2, int a3, int a4, int a5, int a6, long long arg7, float fparg0, float fparg1, long long arg_sp0) {
    struct L *l;
    struct E *e;
    int r;
    r = FUN_001adec0(arg0) & 0xFF;
    l = arg0->list;
    e = (struct E *)*(int *)(l->items + ((l->count - 1) * 4));
    e->f96 = arg_sp0;
    e->f80 = fparg0;
    e->f84 = fparg1 - fparg0;
    e->f88 = arg7;
    e->f72 = 1;
    return r;
}
