typedef struct {
    unsigned char data[32];
    int f32[14];
    int count;
    int f92;
    int len;
    int f100[3];
    unsigned char b112[16];
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
int scePadExitPressMode(int port, int slot) {
    if (padState[port][slot].open == 0) return 0;
    return scePadSetButtonInfo(port, slot, 0);
}
