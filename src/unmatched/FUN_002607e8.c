extern char DAT_00499ce0[];
int FUN_0027e2f0();
int strncpy();
extern int (*DAT_00499cd8)(int, int);
extern int DAT_00499cdc[4];
void FUN_002607e8(int arg0) {
    strncpy(DAT_00499ce0, arg0, 0xFF);
    if (DAT_00499cd8 != 0) {
        DAT_00499cd8(DAT_00499cdc[0], DAT_00499ce0);
    }
    FUN_0027e2f0(DAT_00499ce0);
}
