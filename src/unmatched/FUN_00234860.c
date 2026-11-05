int FUN_001e6d30();
int FUN_002345b0();
extern int DAT_004e96c0[4];
int FUN_00234860(int arg0, int arg1, int arg2, int arg3) {
    int sp2C;

    if (FUN_002345b0(arg0, arg1, arg2, &sp2C) != 0) {
        return FUN_001e6d30(sp2C, arg3, &DAT_004e96c0[0]);
    }
    return 0;
}
