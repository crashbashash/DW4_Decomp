int FUN_00294308();
int FUN_002964a0();
int FUN_002968c0();
int mwsfd_Error();
extern int DAT_004f3a48[4];
int FUN_00296438(int arg0) {
    int temp_s0;

    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f3a48[0]);
        return 0;
    }
    temp_s0 = FUN_002964a0(arg0);
    return temp_s0 + FUN_00294308(arg0);
}
