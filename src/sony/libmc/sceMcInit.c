typedef struct {
    int f0[9];
    int server;
} McClient;
typedef struct {
    int port;
    int f4;
    int f8;
    int rest;
    int f16;
    unsigned int head;
    unsigned char *body;
    int f28;
    unsigned char bytes[16];
} McPkt;
extern McClient DAT_0055d5c0;
extern McPkt DAT_0055d640;
extern int DAT_0055eb80[16];
extern int DAT_00485190;
extern int DAT_00485194;
int FUN_0010af00(int sema);
int FUN_0010af30(int sema);
void FUN_0010b160(int mode);
int sceSifCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
void FUN_00119710(void *arg);
typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    unsigned int attr;
    unsigned int option;
} Sema;
extern char DAT_004d2ad0[];
extern char DAT_004d2ae8[];
extern char DAT_004d2b10[];
extern int DAT_00485198;
int FUN_0010aee0(Sema *s);
int FUN_0010af20(int sema);
void sceSifInitRpc(int mode);
int sceSifBindRpc(void *cd, unsigned int id, int mode);
int scePrintf(const char *fmt, ...);
int sceMcSync(int mode, int *cmd, int *result);
int sceMcInit(void) {
    Sema s;
    int r;
    int i;
    if (DAT_00485194 < 0) {
        s.init_count = 1;
        s.max_count = 1;
        s.option = 0;
        DAT_00485194 = FUN_0010aee0(&s);
        s.init_count = 0;
        s.max_count = 1;
        s.option = 0;
        DAT_00485198 = FUN_0010aee0(&s);
    }
    sceMcSync(0, 0, 0);
    FUN_0010af20(DAT_00485194);
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&DAT_0055d5c0, 0x80000400, 0) < 0) {
            scePrintf(DAT_004d2ad0);
            while (1);
        }
        if (DAT_0055d5c0.server != 0) break;
        i = 0x100000;
        while (--i);
    }
    r = sceSifCallRpc(&DAT_0055d5c0, 254, 0, &DAT_0055d640, 48, DAT_0055eb80, 12, 0, 0);
    FUN_0010af00(DAT_00485194);
    if (r < 0) {
        DAT_0055d5c0.server = 0;
        return r - 100;
    }
    if (DAT_0055eb80[1] < 522) {
        scePrintf(DAT_004d2ae8);
        DAT_0055d5c0.server = 0;
        return -120;
    }
    if (DAT_0055eb80[2] < 526) {
        scePrintf(DAT_004d2b10);
        DAT_0055d5c0.server = 0;
        return -121;
    }
    return DAT_0055eb80[0];
}
