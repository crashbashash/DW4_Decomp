int mwply_GetCurPicCompoMode();

int FUN_002944b0(void) {
    int var_v1;

    var_v1 = mwply_GetCurPicCompoMode();
    if ((var_v1 == 0x51) || (var_v1 == 0x61)) {
        var_v1 = 0x41;
    }
    return var_v1;
}
