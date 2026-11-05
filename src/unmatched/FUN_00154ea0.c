int FUN_00154f30();
int FUN_0015ad50();
int igStrCmp();
extern int DAT_004de6b0[4];
extern int DAT_004de6b8[4];
int FUN_00154ea0(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = FUN_0015ad50(arg1);
    if (temp_v0 != 0) {
        if (igStrCmp(temp_v0, &DAT_004de6b0[0]) != 0) {
            if (igStrCmp(temp_v0, &DAT_004de6b8[0]) == 0) {
                goto block_4;
            }
            goto block_5;
        }
block_4:
        return FUN_00154f30(arg0, arg1);
    }
block_5:
    return 0;
}
