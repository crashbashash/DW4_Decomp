typedef struct {
    unsigned char data[32];
    int f32[14];
    int count;
    int f92;
    int len;
    int f100[7];
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
PadFrame *padGetDmaStr(int port, int slot) {
    PadFrame *p;
    int i;
    p = padState[port][slot].frames;
    FUN_0010b7d8(p, (char *)p + 255);
    i = p[0].count < p[1].count;
    return p + i;
}
