typedef struct {
    int f0[9];
    int server;
} Client;
extern Client DAT_0055d580;
extern int DAT_00485140;
extern int DAT_00485144;
extern char DAT_004d2aa8[];
void sceSifInitRpc(int mode);
int sceSifBindRpc(void *cd, unsigned int id, int mode);
int scePrintf(const char *fmt, ...);
void FUN_0010b160(int mode);
int sceSdRemoteInit(void) {
    int i;
    sceSifInitRpc(0);
    do {
        if (sceSifBindRpc(&DAT_0055d580, 0x80000701, 0) < 0) {
            scePrintf(DAT_004d2aa8);
            return -1;
        }
        i = 10000;
        while (i--);
    } while (DAT_0055d580.server == 0);
    DAT_00485140 = 0;
    DAT_00485144 = 0;
    FUN_0010b160(0);
    return 0;
}
