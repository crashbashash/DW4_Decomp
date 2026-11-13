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
int sceSifCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
void FUN_00119710(void *arg);
int sceMcWrite(int port, unsigned char *buf, int size) {
    unsigned int n;
    unsigned int i;
    int r;
    if (DAT_0055d5c0.server == 0) return -100;
    if (FUN_0010af30(DAT_00485194) < 0) return -200;
    DAT_0055d640.port = port;
    if (size < 17) {
        DAT_0055d640.head = size;
        DAT_0055d640.rest = 0;
        DAT_0055d640.body = 0;
    } else {
        n = (((int)buf - 1) & 0xfffffff0) + 16 - (int)buf;
        DAT_0055d640.head = n;
        DAT_0055d640.rest = size - n;
        DAT_0055d640.body = buf + n;
    }
    for (i = 0; i < DAT_0055d640.head; i++) DAT_0055d640.bytes[i] = buf[i];
    FUN_0010b160(0);
    r = sceSifCallRpc(&DAT_0055d5c0, 6, 1, &DAT_0055d640, 48, &DAT_0055eb80, 4, FUN_00119710, 0);
    if (r == 0) {
        DAT_00485190 = 6;
    } else {
        FUN_0010af00(DAT_00485194);
    }
    return r;
}
