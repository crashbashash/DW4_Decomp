extern int (*DAT_00498c60)(int, int);
extern int DAT_00498c64[4];
int FUN_0025d040(int arg0) {
    if (DAT_00498c60 != 0) {
        DAT_00498c60(DAT_00498c64[0], arg0);
    }
    return 0;
}
