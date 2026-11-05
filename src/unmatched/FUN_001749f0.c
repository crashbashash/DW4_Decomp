int FUN_001e74b0();
int FUN_001e7500();
extern long long DAT_005608b0[2];
extern int DAT_0048a530[4];
typedef struct { char p[1256]; int f; } S;
void FUN_001749f0(S *arg0, int arg1) {
    if (arg0->f == arg1) {
        DAT_005608b0[0] += 1;
    }
    arg0->f = arg1;
    if (DAT_0048a530[arg1] == 1) {
        FUN_001e7500(0x11);
        return;
    }
    FUN_001e74b0(0x11);
}
