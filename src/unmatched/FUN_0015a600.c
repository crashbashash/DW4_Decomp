typedef struct { char pad[8]; int f8; int fc; char pad2[28]; int f2c; char pad3[4]; int f34; char pad4[12]; int f44; } T;
int FUN_00154d40();
int FUN_00159f70();
int FUN_0015a220();
int FUN_0015a280();

int FUN_0015a600(T *arg0) {
    int t;
    if ((FUN_0015a220(arg0->f2c) == 0) && (FUN_00159f70(arg0->f2c) == 0)) {
        return 1;
    }
    t = arg0->f34;
    if (t != 0) {
        FUN_0015a280(t, arg0->f8 * arg0->fc, arg0->f2c);
    }
    if (FUN_00159f70(arg0->f2c) != 0) {
        t = arg0->f44;
        if (t != 0) {
            return FUN_00154d40(t);
        }
    }
    return 1;
}
