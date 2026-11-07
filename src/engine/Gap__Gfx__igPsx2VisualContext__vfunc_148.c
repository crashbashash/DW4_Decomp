typedef int S;
typedef struct C { char pad[580]; int slot[16]; } C;
int FUN_00208f70();
extern int DAT_0048acf0[];
extern int DAT_00560a5c[];
extern int DAT_00569330[4];
extern int DAT_00569340[];
extern int *DAT_0056ad80[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_148(C *arg0, int arg1, int arg2) {
    int a3;
    arg1 = arg1 < 15 ? arg1 : 15;
    if (arg1 < 8) {
        if (arg0->slot[arg1] == arg2) {
            DAT_00560a5c[arg1] += 1;
        }
    }
    arg0->slot[arg1] = arg2;
    a3 = arg1 > 1 ? arg1 - 1 : 0;
    DAT_00569330[0] = arg1;
    DAT_0056ad80[0] = (int *)((char *)DAT_00569340 + a3 * 448);
    FUN_00208f70(DAT_0048acf0[arg2], a3 * 7, arg2);
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}
