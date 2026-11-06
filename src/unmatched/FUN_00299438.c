int FUN_002968c0();
int FUN_002991b0();
int FUN_002994f8();
int FUN_00299510();
int FUN_0029a320();
extern int DAT_004f48c0[4];
extern int DAT_004f48f0[4];
int FUN_00299438(int arg0, int arg1) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f48c0[0]);
        return 0;
    }
    if (arg1 < FUN_002991b0(arg0)) {
        if (arg1 < 0) {
            FUN_0029a320(&DAT_004f48f0[0], arg1);
            return 0;
        }
        return FUN_00299510(arg0, FUN_002994f8(arg0, arg1));
    }
    return 0;
}
