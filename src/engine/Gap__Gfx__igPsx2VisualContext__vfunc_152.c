extern unsigned char GPR_00554b48;
extern int DAT_00560924[4];
int FUN_001e74b0();
int FUN_001e7500();
struct S { char pad[1032]; unsigned char f1032; };

void Gap__Gfx__igPsx2VisualContext__vfunc_152(struct S *arg0, int arg1) {
    if (GPR_00554b48 != 0) {
        arg1 = 0;
    }
    if (arg0->f1032 == (arg1 & 0xFF)) {
        DAT_00560924[0] += 1;
    }
    arg0->f1032 = arg1;
    if (arg0->f1032 != 0) {
        FUN_001e74b0(2, arg1);
        return;
    }
    FUN_001e7500(2, arg1);
}
