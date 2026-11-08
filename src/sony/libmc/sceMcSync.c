extern int DAT_00485190;
extern int DAT_00485194;
extern int DAT_00485198;
extern int DAT_0055eb80;
int FUN_0010af00(int sema);
int FUN_0010af20(int sema);
int FUN_0010af30(int sema);
int sceMcSync(int mode, int *cmd, int *result) {
    int busy;
    if (DAT_00485190 == 0) return -1;
    busy = 0;
    if (FUN_0010af30(DAT_00485198) < 0) busy = 1;
    if (mode == 0 && busy) {
        FUN_0010af20(DAT_00485198);
        busy = 0;
    }
    busy = !busy;
    if (cmd) *cmd = DAT_00485190;
    if (busy) {
        DAT_00485190 = 0;
        if (result) *result = DAT_0055eb80;
        FUN_0010af00(DAT_00485194);
    }
    return busy;
}
