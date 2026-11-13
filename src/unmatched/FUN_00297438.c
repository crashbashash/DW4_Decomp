int FUN_002963a8();
int FUN_002968c0();
int mwsfd_Error();
int FUN_002aa548();
extern int DAT_004f3f98[4];
void FUN_00297438(int arg0, int arg1) {
    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f3f98[0]);
        return;
    }
    FUN_002aa548(FUN_002963a8(arg0), arg1);
}
