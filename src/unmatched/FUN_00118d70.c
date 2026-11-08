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
int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_0010b7d8(void *start, void *end);
void *memcpy(void *dst, const void *src, unsigned int n);
PadFrame *FUN_00118178(int port, int slot);
int FUN_00118bb0(int port, int slot, int mode);
int FUN_00118af8(int port, int slot);
extern int DAT_0055d480[32];
extern int DAT_0055d240;
int FUN_0010e2a8(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
extern int DAT_00485108;
int FUN_00118440(int port, int slot, int v);
typedef struct {
    unsigned char b[12];
} PadAlign;
int FUN_00118d70(int port, int slot, PadAlign *a) {
    int *b;
    b = DAT_0055d480;
    b[0] = 11;
    b[1] = port;
    b[2] = slot;
    *(PadAlign *)&b[3] = *a;
    if (FUN_0010e2a8(&DAT_0055d240, 1, 0, b, 128, b, 128, 0, 0) < 0) return 0;
    if (b[7] == 1) FUN_00118440(port, slot, 2);
    return b[7];
}
