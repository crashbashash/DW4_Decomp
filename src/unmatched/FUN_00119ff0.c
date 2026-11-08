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
extern char DAT_0055dac0[192];
extern int *DAT_0055d5e8;
extern int *DAT_0055d5ec;
extern int *DAT_0055d5f0;
void sceSifWriteBackDCache(void *p, int size);
void mceGetInfoApdx(void *arg);
int FUN_00119ff0(int port, int slot, int *type, int *free, int *format) {
    int r;
    if (DAT_0055d5c0.server == 0) return -100;
    if (FUN_0010af30(DAT_00485194) < 0) return -200;
    DAT_0055d640.f4 = port;
    DAT_0055d640.f8 = slot;
    DAT_0055d640.f28 = (int)DAT_0055dac0;
    if (type) DAT_0055d640.head = 1; else DAT_0055d640.head = 0;
    if (free) DAT_0055d640.f16 = 1; else DAT_0055d640.f16 = 0;
    if (format) DAT_0055d640.rest = 1; else DAT_0055d640.rest = 0;
    DAT_0055d5e8 = type;
    DAT_0055d5ec = free;
    DAT_0055d5f0 = format;
    sceSifWriteBackDCache(DAT_0055dac0, 192);
    r = FUN_0010e2a8(&DAT_0055d5c0, 1, 1, &DAT_0055d640, 48, &DAT_0055eb80, 4, mceGetInfoApdx, DAT_0055dac0);
    if (r == 0) {
        DAT_00485190 = 1;
    } else {
        FUN_0010af00(DAT_00485194);
    }
    return r;
}
