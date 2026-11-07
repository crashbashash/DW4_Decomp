typedef struct S { char pad0[1036]; int f1036; char pad1040[60]; int f1100; } S;
int FUN_00174640();
extern int DAT_00560928[4];
extern int DAT_00560968[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_158(S *arg0, int arg1, int arg2) {
    if (arg0->f1036 == arg1) {
        DAT_00560928[0] += 1;
    }
    if (arg0->f1100 == arg2) {
        DAT_00560968[0] += 1;
    }
    arg0->f1036 = arg1;
    arg0->f1100 = arg2;
    FUN_00174640(arg0, 0);
}
