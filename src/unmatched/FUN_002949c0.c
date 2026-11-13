int FUN_002963a8();
int FUN_002968c0();
int mwsfd_Error();
int FUN_002a8800();
extern int DAT_004f32d8[4];
int FUN_002949c0(int arg0) {
    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f32d8[0]);
        return 0;
    }
    return FUN_002a8800(FUN_002963a8(arg0));
}
