int DeleteSema();
extern int DAT_00485194[4];
extern int DAT_00485198[4];
int FUN_00119690(void) {
    if (DAT_00485194[0] >= 0) {
        DeleteSema(DAT_00485194[0]);
        DAT_00485194[0] = -1;
        DeleteSema(DAT_00485198[0]);
    }
    return 1;
}
