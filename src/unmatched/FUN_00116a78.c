typedef struct {
    int f0[9];
    int server;
} Client;
extern int DAT_00483550;
extern volatile int DAT_00483568;
extern int DAT_0048355c;
extern int DAT_0048357c;
extern int DAT_0055cf98;
extern int DAT_0055cfa0;
extern Client DAT_00484710;
extern char DAT_004d27f0[];
extern char DAT_004d2818[];
void FUN_00116498(void);
int FUN_0010af00(int sema);
int FUN_0010af30(int sema);
int FUN_0010ade0(int id, void *info);
int scePrintf(const char *fmt, ...);
void sceSifInitRpc(int mode);
int sceSifBindRpc(void *cd, unsigned int id, int mode);
int sceCdSync(int mode);
int FUN_00116a78(int cmd) {
    int i;
    FUN_00116498();
    if (DAT_00483568 != FUN_0010af30(DAT_00483568)) {
        if (DAT_00483550 > 0) scePrintf(DAT_004d27f0, cmd, DAT_0048355c);
        return 0;
    }
    DAT_0048355c = cmd;
    FUN_0010ade0(DAT_0055cf98, &DAT_0055cfa0);
    if (sceCdSync(1)) {
        FUN_0010af00(DAT_00483568);
        return 0;
    }
    sceSifInitRpc(0);
    if (DAT_0048357c >= 0) return 1;
    while (1) {
        if (sceSifBindRpc(&DAT_00484710, 0x80000595, 0) < 0) {
            if (DAT_00483550 > 0) scePrintf(DAT_004d2818);
            i = 0x100000;
            while (i--);
            continue;
        }
        if (DAT_00484710.server != 0) break;
        i = 0x100000;
        while (i--);
    }
    DAT_0048357c = 0;
    return 1;
}
