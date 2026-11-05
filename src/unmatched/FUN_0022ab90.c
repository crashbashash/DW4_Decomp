int FUN_0022aac0();
int FUN_0022ac70();
int igObject_IsKindOf();
int FUN_0022ab90(int arg0, int arg1, int arg2) {
    int var_s0;
    int r;
    var_s0 = FUN_0022aac0();
    if (igObject_IsKindOf(var_s0, arg2) != 0) { r = var_s0; } else { var_s0 = FUN_0022ac70(arg0, arg2); r = var_s0; } return r;
}
