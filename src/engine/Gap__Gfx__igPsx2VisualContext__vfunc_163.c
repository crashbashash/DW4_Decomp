typedef struct S0 { char pad1260[1260]; int f4EC; char pad1288[24]; int f508; } S0;
int FUN_001e74b0();
int FUN_001e7500();
int FUN_001e7560();
extern int DAT_005609c0[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_163(S0 *arg0, unsigned int arg1) {
    switch (arg1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if ((arg0->f4EC != 0) && (FUN_001e7560(4) == 0)) {
            FUN_001e74b0(4);
        }
        break;
    case 7:
        FUN_001e7500(4);
        break;
    }
    if (arg0->f508 == arg1) {
        DAT_005609c0[0] += 1;
    }
    arg0->f508 = arg1;
}
