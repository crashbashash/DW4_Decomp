typedef struct Rc { int vt; int rc; int p8; } Rc;
typedef struct Q { char pad8[8]; int f8; } Q;
typedef struct P { char pad28[28]; Q *f28; } P;
typedef struct A { char pad12[12]; int f12; char pad16[8]; Rc *f24; P *f28; unsigned char f32; } A;
typedef struct R { char pad8[8]; Q *f8; } R;
typedef struct V3 { int a; int b; int c; int pad[4]; } V3;
int FUN_001c5d10();
int FUN_001c5eb0();
int FUN_004569c0();
int FUN_004578c0();
int igObject_Destroy();
extern int DAT_0058c3d8[4];
void FUN_00456a60(A *arg0, R *arg1) {
    Rc *sp4C;
    V3 sp30;
    int var_v0;
    Rc *temp_a0;
    P *temp_a1;
    Q *temp_v0;

    if (arg1 != 0) {
        ((Rc *)arg1)->rc = ((Rc *)arg1)->rc + 1;
    }
    temp_a0 = arg0->f24;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if (((unsigned long long)((long long)temp_a0->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f24 = (Rc *)arg1;
    temp_a1 = arg0->f28;
    temp_v0 = temp_a1->f28;
    if (temp_v0 != 0) {
        var_v0 = temp_v0->f8;
    } else {
        var_v0 = 0;
    }
    if (var_v0 > 0) {
        FUN_001c5eb0(&sp4C, temp_a1, 0);
        if (sp4C != 0) {
            sp4C->rc = sp4C->rc - 1;
            if (((unsigned long long)((long long)sp4C->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sp4C);
            }
        }
    }
    if (arg1 != 0) {
        FUN_001c5d10(arg0->f28, arg1->f8->f8);
    }
    FUN_004569c0(arg0, arg0->f32);
    sp30.a = 2;
    sp30.b = 0;
    sp30.c = DAT_0058c3d8[0];
    FUN_004578c0(arg0->f12, &sp30);
}
