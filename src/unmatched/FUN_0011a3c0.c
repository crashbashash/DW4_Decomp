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
extern int DAT_0055eb80;
extern int DAT_00485190;
extern int DAT_00485194;
int FUN_0010af00(int sema);
int FUN_0010af30(int sema);
void FUN_0010b160(int mode);
int FUN_0010e2a8(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
void FUN_00119710(void *arg);
typedef struct {
    int port;
    int slot;
    int f8;
    int f12;
    void *f16;
    char name[1024];
} McNamePkt;
extern McNamePkt DAT_0055d670;
char *FUN_0012ad58(char *dst, const char *src, unsigned int n);
extern char DAT_0055db80[1024];
void sceSifWriteBackDCache(void *p, int size);
void mceStorePwd(void *arg);
int FUN_0011a3c0(int port, int slot, char *name, void *info) {
    int r;
    if (DAT_0055d5c0.server == 0) return -100;
    if (FUN_0010af30(DAT_00485194) < 0) return -200;
    if (name == 0 || *name == 0) {
        FUN_0010af00(DAT_00485194);
        return -210;
    }
    DAT_0055d670.port = port;
    DAT_0055d670.slot = slot;
    DAT_0055d670.f16 = DAT_0055db80;
    FUN_0012ad58(DAT_0055d670.name, name, 1023);
    DAT_0055d670.name[1023] = 0;
    sceSifWriteBackDCache(DAT_0055db80, 1024);
    r = FUN_0010e2a8(&DAT_0055d5c0, 12, 1, &DAT_0055d670, 1044, &DAT_0055eb80, 4, mceStorePwd, info);
    if (r == 0) {
        DAT_00485190 = 12;
    } else {
        FUN_0010af00(DAT_00485194);
    }
    return r;
}
