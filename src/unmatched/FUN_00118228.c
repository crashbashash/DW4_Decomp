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
int FUN_00118228(int port, int slot, void *dst) {
    PadFrame f;
    PadFrame *q;
    int s;
    if (padState[port][slot].open == 0) return 0;
    s = DIntr();
    q = &f;
    *q = *padGetDmaStr(port, slot);
    memcpy(dst, q->data, q->len);
    if (s == 1) EIntr();
    return q->len;
}
