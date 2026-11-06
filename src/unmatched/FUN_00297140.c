int FUN_002963a8();
int FUN_002968c0();
int FUN_0029a320();
int FUN_002ad950();
extern int DAT_004f3ed0[4];
void FUN_00297140(int arg0, int arg1) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f3ed0[0]);
        return;
    }
    FUN_002ad950(FUN_002963a8(arg0), 7, arg1 != 1);
}
