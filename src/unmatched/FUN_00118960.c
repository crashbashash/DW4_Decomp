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
int _send_to_iop(int port, int slot);
int FUN_00118960(int port, int slot, unsigned char *data) {
    int i;
    int *b;
    unsigned char *d;
    if (padGetDmaStr(port, slot)->b[14] != 1) return 0;
    b = (int *)padState[port][slot].f4;
    d = (unsigned char *)&b[3];
    for (i = 0; i < 6; i++) d[i] = data[i];
    b[1] = 1;
    b[2] = 6;
    if (_send_to_iop(port, slot) != 1) return 0;
    return 1;
}
