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
extern PadSlot padState[2][4];
int DIntr(void);
int EIntr(void);
void FUN_0010b7d8(void *start, void *end);
void *memcpy(void *dst, const void *src, unsigned int n);
PadFrame *padGetDmaStr(int port, int slot);
int scePadSetButtonInfo(int port, int slot, int mode);
int FUN_00118af8(int port, int slot);
extern int DAT_0055d480[32];
extern int DAT_0055d240;
int sceSifCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
extern int DAT_00485108;
int FUN_00118440(int port, int slot, int v);
int FUN_00117db8(void) {
    int i;
    for (i = 0; i < 4; i++) {
        padState[0][i].open = 0;
        padState[0][i].f24 = 0;
        padState[0][i].f20 = 0;
        padState[1][i].open = 0;
        padState[1][i].f24 = 0;
        padState[1][i].f20 = 0;
    }
    DAT_0055d480[0] = 16;
    DAT_0055d480[4] = 0;
    if (sceSifCallRpc(&DAT_0055d240, 1, 0, DAT_0055d480, 128, DAT_0055d480, 128, 0, 0) < 0) return 0;
    return DAT_0055d480[3];
}
