int FUN_0010d108();
int FUN_0010f330();
int FUN_00272688();
int FUN_002726c0();
extern int DAT_004efec0[4];
int FUN_002728b0(int arg0, int arg1) {
    int temp_v0;

    FUN_00272688();
    temp_v0 = FUN_0010f330(arg0, arg1);
    if (temp_v0 < 0) {
        FUN_0010d108(&DAT_004efec0[0], temp_v0);
    }
    FUN_002726c0();
    return temp_v0;
}
