typedef struct S { char pad0[8]; int f8; int f12; char pad16[28]; int f44; char pad48[4]; int f52; char pad56[12]; int f68; } S;
int FUN_00154b40();
int FUN_00159f70();
int FUN_0015a220();
int FUN_0015a300();

int FUN_0015a380(S *arg0) {
    if ((FUN_0015a220(arg0->f44) == 0) && (FUN_00159f70(arg0->f44) == 0)) {
        return 1;
    }
    if (arg0->f52 != 0) {
        FUN_0015a300(arg0->f52, arg0->f8 * arg0->f12, arg0->f44);
    }
    if (FUN_00159f70(arg0->f44) != 0 && arg0->f68 != 0) {
        return FUN_00154b40(arg0->f68);
    }
    return 1;
}
