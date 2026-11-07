struct S { char pad[1300]; unsigned char mode; };
int FUN_001e74b0(int, int);
int FUN_001e7500(int, int);
extern int DAT_005609cc[4];
extern unsigned char GPR_00554b60;
void Gap__Gfx__igPsx2VisualContext__vfunc_241(struct S *arg0, int arg1) {
    if (GPR_00554b60 != 0) {
        arg1 = 0;
    }
    if (arg0->mode == (arg1 & 0xFF)) {
        DAT_005609cc[0] += 1;
    }
    arg0->mode = arg1;
    if (arg1 != 0) {
        FUN_001e74b0(7, arg1);
        return;
    }
    FUN_001e7500(7, arg1);
}
