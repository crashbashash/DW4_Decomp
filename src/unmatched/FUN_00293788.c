int FUN_002937d8();
int FUN_002968c0();
int mwsfd_Error();
extern int DAT_004f30d0[4];
int FUN_00293788(int arg0) {
    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f30d0[0]);
        return 0;
    }
    return FUN_002937d8(arg0);
}
