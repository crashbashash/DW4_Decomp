int FUN_00276338();

int FUN_00276350(char arg0, char arg1) {
    int temp_s0;

    temp_s0 = FUN_00276338(arg0);
    return ((temp_s0 ^ FUN_00276338(arg1)) != 0) ? -1 : 0;
}
