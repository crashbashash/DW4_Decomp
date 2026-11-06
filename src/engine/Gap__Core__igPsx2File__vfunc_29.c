int FUN_0010f738();
int FUN_0010fbd0();
int memcpy();
int FUN_0032b5b0();
typedef struct F { char p[20]; int f20; int f24; char q[16]; int f44; char r[4]; int f52; int f56; int f60; } F;
int Gap__Core__igPsx2File__vfunc_29(F *arg0, int arg1, int arg2, int arg3) {
    int s0;
    if (arg0->f24 < 0) return -1;
    if (arg2 == 0) return 0;
    if (arg0->f60 == 1) {
        if (arg0->f20 == 6) {
            FUN_0010f738(arg0->f24, 0, 2);
        }
        return FUN_0010fbd0(arg0->f24, arg1, arg3 * arg2) / arg2;
    }
    s0 = arg2 * arg3;
    if (arg0->f20 == 2) {
        arg0->f52 = arg0->f56;
    }
    FUN_0032b5b0(arg0, arg0->f52 + s0);
    memcpy(arg0->f44 + arg0->f52, arg1, s0);
    arg0->f52 = arg0->f52 + s0;
    return s0 / arg2;
}
