struct L { char p8[8]; int n; char p12[4]; int *data; };
struct B { char p32[32]; struct L *f32; };
struct A { char p52[52]; int f52; };
int FUN_001b06f0();
int FUN_001b0aa0();
int FUN_001e07a0();

int FUN_001b9fc0(struct A *arg0, struct B *arg1) {
    int s1;
    int s0;

    s0 = arg1->f32->n;
    for (s1 = 0; s1 < s0; s1++) {
        FUN_001b06f0(arg0->f52, arg1->f32->data[s1], 0);
    }
    FUN_001e07a0(arg0, arg1);
    for (s0 = s0 - 1; s0 >= 0; s0--) {
        FUN_001b0aa0(arg0->f52, arg1->f32->data[s0], 0);
    }
    return 0;
}
