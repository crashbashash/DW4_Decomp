int FUN_002968c0();
int FUN_002995e0();
int mwsfd_Error();
extern int DAT_004f4780[4];
void FUN_00299168(int arg0) {
    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f4780[0], 0);
        return;
    }
    FUN_002995e0(arg0, 0);
}
