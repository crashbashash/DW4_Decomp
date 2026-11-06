extern int DAT_0048dce0[4];
extern int DAT_0048dce8[4];
extern int DAT_00491478[4];
void FUN_001e96d0(int arg0, int arg1) {
    if ((DAT_0048dce0[0] != arg0) || (DAT_0048dce8[0] != arg1)) {
        DAT_00491478[0] |= 0x81;
    }
    DAT_0048dce0[0] = arg0;
    DAT_0048dce8[0] = arg1;
}
