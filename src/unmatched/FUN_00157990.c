typedef struct S_arg0 { char p0[8]; int f8; int f12; int f16; char p1[8]; int f28; int f32; int f36; int f40; int f44; char p2[16]; int f64; char p3[4]; int f72; char p4[8]; int f84; } S_arg0;
int FUN_00159320();
int FUN_00159a80();
int FUN_0015a270();

void FUN_00157990(S_arg0 *arg0, int arg1) {
    int sp4C;
    int sp48;
    int sp44;
    int sp40;
    int sp3C;
    int sp38;
    int sp34;
    int sp30;
    int sp2C;
    int sp28;

    arg0->f44 = arg1;
    if (FUN_0015a270(arg0->f44) == 0) {
        FUN_00159a80(arg0->f44, &sp44, &sp40, &sp3C, &sp38, &sp34, &sp30, &sp2C);
        arg0->f64 = sp44;
        arg0->f72 = sp40;
        arg0->f28 = sp3C;
        arg0->f32 = sp38;
        arg0->f36 = sp34;
        arg0->f40 = sp30;
        arg0->f84 = sp2C;
        FUN_00159320(arg0, arg0->f44, arg0->f8, arg0->f12, &sp4C, &sp28, &sp48);
        arg0->f16 = sp28;
    }
}
