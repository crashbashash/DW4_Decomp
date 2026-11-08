int FUN_00154f30();
int FUN_0015ad50();
int strcmp();
extern int DAT_004de6b0[4];
extern int DAT_004de6b8[4];
int Gap__Gfx__igClut__vfunc_23(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = FUN_0015ad50(arg1);
    if (temp_v0 != 0) {
        if (strcmp(temp_v0, &DAT_004de6b0[0]) != 0) {
            if (strcmp(temp_v0, &DAT_004de6b8[0]) == 0) {
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
