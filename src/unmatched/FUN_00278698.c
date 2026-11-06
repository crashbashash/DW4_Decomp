extern int (*DAT_004b0e0c)(int, int);
extern int DAT_004b0e10[4];
void FUN_00278698(int arg0) {
    if (DAT_004b0e0c != 0) {
        DAT_004b0e0c(DAT_004b0e10[0], arg0);
    }
}
