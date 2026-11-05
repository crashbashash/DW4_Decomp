typedef struct S { char p[892]; float f892; unsigned f896; unsigned f900; char q[376]; unsigned f1280; } S;
int FUN_00174db0(S *);
extern int DAT_005609b0[4];
void FUN_00174c50(S *arg0, unsigned arg1) {
    if (arg0->f1280 == arg1) {
        DAT_005609b0[0] += 1;
    }
    arg0->f1280 = arg1;
    FUN_00174db0(arg0);
    if (arg0->f1280 & 4) {
        arg0->f900 = (unsigned)(2147483648.0f * arg0->f892);
    } else {
        arg0->f900 = (unsigned)(2147483648.0f * (1.0f - arg0->f892));
    }
}
