int FUN_00304430();
int FUN_00304680();
int FUN_00320ea0();
int FUN_00322040();
extern int DAT_004fe370[4];
void Gap__Core__igElfFile__vfunc_31(int *arg0) {
    int temp_a1;
    int var_s0;
    temp_a1 = arg0[19];
    FUN_00304430(&DAT_004fe370[0], temp_a1, temp_a1);
    FUN_00304680();
    for (var_s0 = 0; var_s0 < arg0[19]; var_s0++) {
        FUN_00322040(arg0, var_s0, FUN_00320ea0(arg0, var_s0));
    }
}
