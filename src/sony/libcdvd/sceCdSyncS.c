extern int DAT_00483550;
extern int DAT_004850c0;
extern int DAT_004d2840;
int DelayThread(int usec);
int scePrintf(void *p);
int FUN_0010e4a0(void *p);
int sceCdSyncS(int mode) {
    if (mode == 0) {
        if (DAT_00483550 > 0) scePrintf(&DAT_004d2840);
        while (FUN_0010e4a0(&DAT_004850c0)) DelayThread(4000);
        return 0;
    }
    return FUN_0010e4a0(&DAT_004850c0);
}
