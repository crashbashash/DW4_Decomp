int strlen();
extern char DAT_00491910[];
extern int DAT_004964d0[4];
extern int DAT_0056c2a8[4];
extern int DAT_0056c2b0[4];
int FUN_0020d790(int arg0, int arg1) {
    int len;
    int i;
    len = strlen(&DAT_00491910[0]);
    DAT_0056c2b0[0] = arg1;
    if (DAT_004964d0[0] != 0) {
        DAT_0056c2a8[0] = len;
        for (i = 0; i < len; i++) {
            if (DAT_00491910[i] == 0x3B) {
                DAT_00491910[i] = 0;
            }
        }
        DAT_004964d0[0] = 0;
    }
    return 1;
}
