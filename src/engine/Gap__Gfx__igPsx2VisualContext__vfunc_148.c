typedef struct VisualContextSlots { char pad[580]; int slot[16]; } VisualContextSlots;
typedef struct RowBlock { int w[112]; } RowBlock;
int FUN_00208f70(int);
extern int DAT_0048acf0[];
extern int DAT_00560a5c[];
extern int DAT_00569330[4];
extern RowBlock DAT_00569340[];
extern RowBlock *DAT_0056ad80[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_148(VisualContextSlots *arg0, int arg1, int arg2) {
    int a3;
    arg1 = arg1 < 15 ? arg1 : 15;
    if (arg1 < 8) {
        if (arg0->slot[arg1] == arg2) {
            DAT_00560a5c[arg1] += 1;
        }
    }
    arg0->slot[arg1] = arg2;
    a3 = arg1 > 1 ? arg1 - 1 : 0;
DAT_00569330[0] = arg1; DAT_0056ad80[0] = &DAT_00569340[a3]; FUN_00208f70(DAT_0048acf0[arg2]);
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}
