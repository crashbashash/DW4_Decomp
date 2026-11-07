extern int (*DAT_00586f50)();

int FUN_002f0060(int arg0, int arg1, int arg2) {
    if (DAT_00586f50 != 0) {
        return DAT_00586f50();
    }
    return arg2 == 4;
}
