int strncmp();
extern int DAT_004f5a40[4];
int FUN_002b5360(int arg0, int arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    return strncmp(arg0 + 0x13, &DAT_004f5a40[0], 1) == 0;
}
