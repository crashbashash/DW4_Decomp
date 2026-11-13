extern int DAT_00485108;
int scePadGetModVersion(void);
typedef struct {
    int f0[9];
    int server;
} PadClient;
extern PadClient DAT_0055d240[2];
extern int DAT_0048510c;
extern char DAT_004d2998[];
extern char DAT_004d29c0[];
int sceSifBindRpc(void *cd, unsigned int id, int mode);
int scePrintf(const char *fmt, ...);
int FUN_00117db8(int mode);
int FUN_00117c78(int mode) {
    int i;
    int r;
    DAT_00485108 = 1;
    while (1) {
        sceSifBindRpc(&DAT_0055d240[0], 0x80000100, 0);
        if (DAT_0055d240[0].server != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        sceSifBindRpc(&DAT_0055d240[1], 0x80000101, 0);
        if (DAT_0055d240[1].server != 0) break;
        i = 0x10000;
        while (i--);
    }
    r = scePadGetModVersion();
    if (r >> 8 != 4) {
        if (DAT_0048510c) {
            scePrintf(DAT_004d2998);
            scePrintf(DAT_004d29c0, 4, 0, r >> 8, r & 0xff);
        }
        return 0;
    }
    return FUN_00117db8(mode);
}
