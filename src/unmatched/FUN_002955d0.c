int FUN_00295658();
int FUN_002968c0();
int FUN_0029a320();
extern int DAT_004f3758[4];
extern int DAT_004f3788[4];
void FUN_002955d0(int arg0, int arg1) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f3758[0]);
        return;
    }
    if (arg1 == 0) {
        FUN_0029a320(&DAT_004f3788[0]);
        return;
    }
    FUN_00295658(arg0, arg1, 0, -1);
}
