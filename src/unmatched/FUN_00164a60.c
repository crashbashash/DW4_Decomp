extern char DAT_00554b24[4];
extern int DAT_00560688[4];
extern int DAT_0056068c[4];
extern int DAT_00561098[4];
extern int DAT_00586858[4];
int *FUN_00164a60(void) {
    if (DAT_00554b24[0] == 0) {
        DAT_00554b24[0] = 1;
        DAT_00560688[0] = DAT_00586858[0];
        DAT_0056068c[0] = DAT_00561098[0];
    }
    return &DAT_00560688[0];
}
