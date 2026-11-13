int FUN_002968c0();
int mwsfd_Error();
int FUN_0029af28();
extern int DAT_004f4ae0[4];
int FUN_0029af40(int arg0) {
    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f4ae0[0]);
        return 0;
    }
    return FUN_0029af28(arg0) != 1;
}
