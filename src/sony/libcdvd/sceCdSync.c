extern int DAT_00483550;
extern int DAT_00483574;
extern int DAT_00484710;
extern char DAT_004d2830[];
int FUN_0010d108(const char *fmt, ...);
int DelayThread(int usec);
int FUN_0010e4a0(void *p);
int sceCdSync(int mode) {
    if (mode == 0) {
        if (DAT_00483550 > 0) FUN_0010d108(DAT_004d2830);
        while (DAT_00483574 || FUN_0010e4a0(&DAT_00484710)) DelayThread(4000);
        return 0;
    }
    if (DAT_00483574 || FUN_0010e4a0(&DAT_00484710)) return 1;
    return 0;
}
