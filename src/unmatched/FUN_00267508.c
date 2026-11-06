extern int (*DAT_004a5d5c)(int, int);
extern int DAT_004a5d60[4];
int FUN_00267508(int arg0) {
    if (DAT_004a5d5c != 0) {
        DAT_004a5d5c(DAT_004a5d60[0], arg0);
    }
    return 0;
}
