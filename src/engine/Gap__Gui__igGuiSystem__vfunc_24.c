typedef struct B { char pad20[20]; float f14; float f18; char pad28[132]; unsigned char fa0; char pada1[15]; int fb0; } B;
typedef struct A { char pad12[12]; B *fc; } A;
int FUN_004578c0();
extern int DAT_0058c3d8[4];
int Gap__Gui__igGuiSystem__vfunc_24(A *arg0, float fparg0, float fparg1) {
    struct { int a; int b; int c; } s;
    B *temp_v1;

    temp_v1 = arg0->fc;
    if (temp_v1->fa0 == 0) {
        return 0;
    }
    temp_v1->f14 = fparg0;
    temp_v1->f18 = fparg1;
    s.a = 2;
    s.b = 0;
    s.c = DAT_0058c3d8[0];
    FUN_004578c0(arg0->fc, &s);
    return arg0->fc->fb0 != 0;
}
