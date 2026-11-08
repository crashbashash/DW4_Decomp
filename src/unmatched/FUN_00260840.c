extern char DAT_00499ce0[];
int strncat();
int FUN_0027e2f0();
int strncpy();
extern int (*DAT_00499cd8)(int, int);
extern int DAT_00499cdc[4];
void FUN_00260840(int arg0, int arg1) {
    strncpy(DAT_00499ce0, arg0, 0xFF);
    strncat(DAT_00499ce0, arg1, 0xFF);
    if (DAT_00499cd8 != 0) {
        DAT_00499cd8(DAT_00499cdc[0], DAT_00499ce0);
    }
    FUN_0027e2f0(DAT_00499ce0);
}
