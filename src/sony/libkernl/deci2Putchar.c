extern int DAT_00481e60;
extern char DAT_00555e80[128];
int FUN_0010c240(char *);
void deci2Putchar(int c) {
    int n = DAT_00481e60;
    if (n >= 126) {
        DAT_00481e60 = 0;
        DAT_00555e80[127] = 0;
        FUN_0010c240(DAT_00555e80);
        n = DAT_00481e60;
    }
    if (c == '\n') {
        DAT_00481e60 = 0;
        DAT_00555e80[n] = c;
        DAT_00555e80[n + 1] = 0;
        FUN_0010c240(DAT_00555e80);
        return;
    }
    DAT_00481e60 = n + 1;
    DAT_00555e80[n] = c;
}
