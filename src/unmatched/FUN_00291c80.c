int FUN_00291b70();
int FUN_00291c28();
int mwsfd_Error();
extern int DAT_004f2b88[4];
int FUN_00291c80(int arg0) {
    int temp_s0;

    if (arg0 == 0) {
        mwsfd_Error(&DAT_004f2b88[0]);
        return 0;
    }
    temp_s0 = FUN_00291b70();
    return temp_s0 + FUN_00291c28(arg0);
}
