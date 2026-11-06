int FUN_002963a8();
int FUN_002968c0();
int FUN_0029a320();
int FUN_002a8800();
extern int DAT_004f32d8[4];
int FUN_002949c0(int arg0) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f32d8[0]);
        return 0;
    }
    return FUN_002a8800(FUN_002963a8(arg0));
}
