int strncmp();
extern int DAT_004f5a28[4];
int FUN_002b5320(int arg0, int arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    return strncmp(arg0 + 0x12, &DAT_004f5a28[0], 1) == 0;
}
