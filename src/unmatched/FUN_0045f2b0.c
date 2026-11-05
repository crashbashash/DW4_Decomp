typedef struct T { char pad[60]; unsigned char f60; } T;
typedef struct L { char pad[8]; int f8; int pad2; int *f16; } L;
typedef struct C { char pad[192]; unsigned char f192; } C;
typedef struct A { char pad[12]; C *f12; char pad2[24]; int f40; char pad3[20]; L *f64; char pad4[12]; struct { char pad[52]; T *f52; } *f80; } A;
int FUN_001b06f0();

void FUN_0045f2b0(A *arg0) {
    T *t;
    int n;
    int i;

    t = arg0->f80->f52;
    FUN_001b06f0(t, arg0->f40, 0);
    if (t->f60 == 0 && arg0->f12->f192 == 0) {
        n = arg0->f64->f8;
        for (i = 0; i < n; i++) {
            FUN_001b06f0(t, arg0->f64->f16[i], 1);
        }
    }
}
