struct R { int vt; unsigned int rc; };
struct L { char pad[8]; int f8; };
struct S { char pad[28]; struct L *f28; int f32; };
int FUN_001b1e50();
int FUN_001c5eb0();
int igObject_Destroy();
struct R *FUN_001dc9a0(struct S *arg0, int arg1) {
    struct R *sp3C;
    struct R *s0;
    int var_a1;

    FUN_001c5eb0(&sp3C, arg0, arg1);
    s0 = sp3C;
    if (s0 != 0) {
        s0->rc = s0->rc - 1;
        if ((sp3C->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(sp3C);
        }
    }
    {
        int a0v = arg0->f32;
        if (arg0->f28 != 0) {
            var_a1 = arg0->f28->f8;
        } else {
            var_a1 = 0;
        }
        FUN_001b1e50(a0v, var_a1);
    }
    return s0;
}