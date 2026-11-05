/* 0x002d16a0 — FUN_002d16a0. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_002b9470();
int FUN_002b9620();
int FUN_002bad40();
int FUN_002bb200();
int FUN_002c4d80();
int FUN_002d1690();
int FUN_002d18d0();
int FUN_002d1930();
int FUN_002d1a00();
int FUN_002d1e40();
int FUN_0032d1f0();
int thunk_FUN_00126308();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_00530d80[4];
extern int DAT_00586dc8[4];
extern long long DAT_00586dd8[4];
void FUN_002d16a0(int arg0) {
    int *sp2C;
    int var_v0;

    if (DAT_00586dd8[0]++ == 0) {
        DAT_004fb410[0] = 0;
        DAT_004fb418[0] = 1;
        FUN_0032d1f0();
        var_v0 = thunk_FUN_00126308(0x3A0);
        if (var_v0 != 0) {
            var_v0 = FUN_002d1930(var_v0);
        }
        DAT_00586dc8[0] = var_v0;
        FUN_002d1a00(var_v0);
        FUN_002b9620();
        FUN_002b9470();
        FUN_002c4d80();
        FUN_002bb200();
        FUN_002bad40();
        sp2C = (int *)(&DAT_00530d80[0]);
        FUN_002d1690(&sp2C);
        FUN_002d1e40(DAT_00586dc8[0]);
    }
    FUN_002d18d0(DAT_00586dc8[0], arg0);
}
