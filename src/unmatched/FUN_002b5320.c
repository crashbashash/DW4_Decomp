int FUN_0012aba0();
extern int DAT_004f5a28[4];
int FUN_002b5320(int arg0, int arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    return FUN_0012aba0(arg0 + 0x12, &DAT_004f5a28[0], 1) == 0;
}
