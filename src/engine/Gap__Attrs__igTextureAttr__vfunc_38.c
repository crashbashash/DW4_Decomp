typedef struct T { char p[88]; int f88; } T;
typedef struct Arg { char p[16]; int f16; int f20; int f24; int f28; int f32; char p2[4]; int f40; int f44; char p3[4]; unsigned char f52; } Arg;
int FUN_00129ef8();
int *FUN_001405a0();
T *FUN_00140c00();
int igStrCmp();
extern int DAT_004d5df8[4];
extern int DAT_004d5e10[4];
int Gap__Attrs__igTextureAttr__vfunc_38(Arg *arg0, int arg1) {
    int sp206C;
    int sp2068;
    int sp2064;
    int sp2060;
    int sp205C;
    int sp2058;
    int sp2054;
    int sp2050;
    char sp50[8192];
    int *var_a1;
    int *var_s1;

    if (FUN_00129ef8(arg1, &DAT_004d5e10[0], sp50, &sp206C, &sp2068, &sp2064, &sp2060, &sp205C, &sp2058, &sp2054, &sp2050) != 9) {
        return 0;
    }
    var_s1 = (int *)(&DAT_004d5df8[0]);
    var_a1 = (int *)(&DAT_004d5df8[0]);
    if (FUN_00140c00(arg0, 0) != 0) {
        if (FUN_00140c00(arg0, 0)->f88 != 0) {
            var_s1 = (int *)(FUN_001405a0(FUN_00140c00(arg0, 0)->f88));
        }
        var_a1 = (int *)(var_s1);
    }
    if (igStrCmp(sp50, var_a1) == 0) {
        if (sp206C == arg0->f16) {
            if ((sp2068 == arg0->f20) && (sp2064 == arg0->f24) && (sp2060 == arg0->f28) && (sp205C == arg0->f32) && (sp2058 == arg0->f40) && (sp2054 == arg0->f44) && (sp2050 == arg0->f52)) {
                return 1;
            }
        }
    }
    return 0;
}
