typedef struct S0 { char pad1296[1296]; int f510; } S0;
extern int DAT_005609c8[4];
void FUN_00175090(S0 *arg0, int arg1) {
    if (arg0->f510 == arg1) {
        DAT_005609c8[0] += 1;
    }
    arg0->f510 = arg1;
}
