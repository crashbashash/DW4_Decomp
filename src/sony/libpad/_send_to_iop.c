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
typedef struct {
    unsigned int src;
    unsigned int dest;
    int size;
    int attr;
} DmaData;
extern int DAT_0048510c;
extern char DAT_004d2950[];
int scePrintf(const char *fmt, ...);
int FUN_0010b280(int id);
int FUN_0010b2a0(DmaData *d, int n);
int _send_to_iop(int port, int slot) {
    DmaData dma[16];
    int *b;
    unsigned int dst;
    int id;
    int n;
    b = (int *)padState[port][slot].f4;
    if (padState[port][slot].f12 != 0) {
        if (FUN_0010b280(padState[port][slot].f12) >= 0) {
            if (DAT_0048510c) scePrintf(DAT_004d2950);
            return 0;
        }
    }
    n = b[0] + 1;
    dst = padState[port][slot].f8 + ((n & 1) << 5);
    b[0] = n;
    FUN_0010b7d8(b, (char *)b + 31);
    dma[0].dest = dst;
    dma[0].src = (unsigned int)b;
    dma[0].size = 32;
    dma[0].attr = 0;
    id = FUN_0010b2a0(dma, 1);
    if (id == 0) {
        if (DAT_0048510c) scePrintf(DAT_004d2950);
        return 0;
    }
    padState[port][slot].f12 = id;
    return 1;
}
