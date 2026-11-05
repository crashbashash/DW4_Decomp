int printf();
extern int DAT_00490b70[];
extern int DAT_004e4c00[];
extern short DAT_00568e10[];
void FUN_001ebb10(int arg0) {
    int t;
    switch (arg0) {
    case 1:
    case 2:
        DAT_00490b70[0] = arg0;
        break;
    default:
        printf(&DAT_004e4c00[0], arg0);
        break;
    }
    t = DAT_00490b70[0];
    DAT_00568e10[0] = (short) t;
}
