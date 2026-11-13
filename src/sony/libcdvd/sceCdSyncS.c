extern int DAT_00483550;
extern int DAT_004850c0;
extern int DAT_004d2840;
int DelayThread(int usec);
int scePrintf(void *p);
int sceSifCheckStatRpc(void *p);
int sceCdSyncS(int mode) {
    if (mode == 0) {
        if (DAT_00483550 > 0) scePrintf(&DAT_004d2840);
        while (sceSifCheckStatRpc(&DAT_004850c0)) DelayThread(4000);
        return 0;
    }
    return sceSifCheckStatRpc(&DAT_004850c0);
}
