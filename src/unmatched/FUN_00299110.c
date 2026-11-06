int FUN_002968c0();
int FUN_00299010();
int FUN_00299168();
int FUN_0029a320();
extern int DAT_004f4750[4];
void FUN_00299110(int arg0) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f4750[0], 0);
        return;
    }
    FUN_00299010(arg0, 0);
    FUN_00299168(arg0);
}
