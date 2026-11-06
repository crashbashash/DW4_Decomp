int FUN_00274668();

int FUN_002746a0(char arg0, char arg1) {
    int temp_s0;

    temp_s0 = FUN_00274668(arg0);
    return ((temp_s0 ^ FUN_00274668(arg1)) != 0) ? -1 : 0;
}
