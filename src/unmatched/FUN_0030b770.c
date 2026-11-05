int FUN_0030b3c0();
extern int DAT_004f9590[4];
extern int DAT_004f9598[4];
extern int DAT_004fb430[4];
extern int DAT_004fb438[4];
void FUN_0030b770(int arg0, int arg1, int arg2) {
    int *var_a1;
    int *var_a1_2;

    if (arg2 != 0) {
        if (arg1 != 0) {
            var_a1 = (int *)(&DAT_004fb430[0]);
        } else {
            var_a1 = (int *)(&DAT_004fb438[0]);
        }
        FUN_0030b3c0(arg0, var_a1);
        return;
    }
    if (arg1 != 0) {
        var_a1_2 = (int *)(&DAT_004f9590[0]);
    } else {
        var_a1_2 = (int *)(&DAT_004f9598[0]);
    }
    FUN_0030b3c0(arg0, var_a1_2);
}