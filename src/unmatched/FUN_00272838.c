int FUN_0010d108();
int FUN_0010fe90();
int FUN_00272688();
int FUN_002726c0();
extern int DAT_004efea0[4];
int FUN_00272838(int arg0, int arg1, int arg2) {
    int temp_v0;

    FUN_00272688();
    temp_v0 = FUN_0010fe90(arg0, arg1, arg2);
    if (temp_v0 < 0) {
        FUN_0010d108(&DAT_004efea0[0], temp_v0);
    }
    FUN_002726c0();
    return temp_v0;
}
