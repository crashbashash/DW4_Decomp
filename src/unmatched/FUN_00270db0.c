extern int DAT_004a927c[4];
extern int DAT_004a9280[4];
void FUN_00270db0(int arg0, int arg1) {
    if (arg0 == 0) {
        DAT_004a927c[0] = 0;
        DAT_004a9280[0] = 0;
        return;
    }
    DAT_004a927c[0] = arg0;
    DAT_004a9280[0] = arg1;
}
