int FUN_00291b70();
int FUN_00291c28();
int FUN_0029a320();
extern int DAT_004f2b88[4];
int FUN_00291c80(int arg0) {
    int temp_s0;

    if (arg0 == 0) {
        FUN_0029a320(&DAT_004f2b88[0]);
        return 0;
    }
    temp_s0 = FUN_00291b70();
    return temp_s0 + FUN_00291c28(arg0);
}
