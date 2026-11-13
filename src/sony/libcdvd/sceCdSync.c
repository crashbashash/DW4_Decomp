extern int DAT_00483550;
extern int DAT_00483574;
extern int DAT_00484710;
extern char DAT_004d2830[];
int scePrintf(const char *fmt, ...);
int DelayThread(int usec);
int sceSifCheckStatRpc(void *p);
int sceCdSync(int mode) {
    if (mode == 0) {
        if (DAT_00483550 > 0) scePrintf(DAT_004d2830);
        while (DAT_00483574 || sceSifCheckStatRpc(&DAT_00484710)) DelayThread(4000);
        return 0;
    }
    if (DAT_00483574 || sceSifCheckStatRpc(&DAT_00484710)) return 1;
    return 0;
}
