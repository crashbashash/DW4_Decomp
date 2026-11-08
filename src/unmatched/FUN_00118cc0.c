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
extern PadSlot DAT_0055d290[2][4];
int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_0010b7d8(void *start, void *end);
void *memcpy(void *dst, const void *src, unsigned int n);
PadFrame *FUN_00118178(int port, int slot);
int FUN_00118bb0(int port, int slot, int mode);
int FUN_00118af8(int port, int slot);
int FUN_00118cc0(int port, int slot) {
    if (DAT_0055d290[port][slot].open == 0) return 0;
    return FUN_00118bb0(port, slot, 4095);
}
