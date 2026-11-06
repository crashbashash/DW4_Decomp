int FUN_00260c20();
int FUN_00261778();
int FUN_00261960();
int FUN_00261c88();

int FUN_002619e0(int arg0, int arg1, int arg2, int arg3) {
    int temp_a0;
    int var_s2;

    FUN_00260c20(1, 0, arg0, arg1, -1);
    var_s2 = FUN_00261778();
    if (var_s2 != 0) {
        if (FUN_00261960(var_s2, arg0, arg1, arg2, arg3) < 0) {
            temp_a0 = var_s2;
            var_s2 = 0;
            FUN_00261c88(temp_a0);
        }
    }
    FUN_00260c20(1, 1, arg0, arg1, -1);
    return var_s2;
}
