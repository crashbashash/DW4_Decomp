typedef struct {
    unsigned char data[32];
    int f32[14];
    int count;
    int f92;
    int len;
    unsigned char b[28];
} PadFrame;
typedef struct {
    PadFrame *frames;
    int f4;
    int f8;
    int f12;
    int open;
    int f20;
    int f24;
} PadSlot;
extern PadSlot DAT_0055d290[2][4];
extern int DAT_0055d480[32];
extern int DAT_0055d240;
int sceSifCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
int scePadPortClose(int port, int slot) {
    if (DAT_0055d290[port][slot].open == 0) return 0;
    DAT_0055d480[0] = 14;
    DAT_0055d480[1] = port;
    DAT_0055d480[2] = slot;
    DAT_0055d480[4] = 1;
    if (sceSifCallRpc(&DAT_0055d240, 1, 0, DAT_0055d480, 128, DAT_0055d480, 128, 0, 0) < 0) return 0;
    DAT_0055d290[port][slot].open = 0;
    return DAT_0055d480[3];
}
