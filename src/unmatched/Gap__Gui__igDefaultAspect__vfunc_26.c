int FUN_001c5eb0();
int FUN_004578c0();
int igObject_Destroy();
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_0058c468[4];

typedef struct R { int w0; int refs; } R;
typedef struct T { char pad[16]; float f16; float f20; float f24; } T;
typedef struct L { char pad[8]; int count; } L;
typedef struct A { char pad[8]; T *f8; int f12; char pad16[24]; L *f40; } A;

void Gap__Gui__igDefaultAspect__vfunc_26(A *arg0) {
    R *sp4C;
    int sp30[7];
    int var_s0;
    T *temp_v1;

    var_s0 = arg0->f40->count - 1;
    while (var_s0 >= 0) {
        FUN_001c5eb0(&sp4C, arg0->f12, var_s0);
        if (sp4C != 0) {
            sp4C->refs = sp4C->refs - 1;
            if (((unsigned long long)((long long)sp4C->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sp4C);
            }
        }
        var_s0 -= 1;
    }
    temp_v1 = arg0->f8;
    temp_v1->f16 = DAT_004e1058[0];
    temp_v1->f20 = DAT_004e105c[0];
    temp_v1->f24 = DAT_004e1060[0];
    sp30[0] = 2;
    sp30[1] = 0;
    sp30[2] = DAT_0058c468[0];
    FUN_004578c0(arg0->f8, &sp30[0]);
}
