typedef struct {
    unsigned char data[32];
    int f32[4];
    unsigned char modes[8][4];
    unsigned short table[4];
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
int FUN_00118770(int port, int slot, int term, int offs) {
    PadFrame *p;
    if (DAT_0055d290[port][slot].open == 0) return 0;
    p = FUN_00118178(port, slot);
    if (p->b[14] != 1) return 0;
    if (p->b[13] == 2) return 0;
    switch (term) {
    case 1:
        if (p->b[1] == 0xf3) return 0;
        return p->b[1] >> 4;
    case 2:
        if (p->b[0] == 1) return 0;
        return p->table[p->b[5]];
    case 3:
        if (p->b[0] == 1) return 0;
        return p->b[5];
    case 4:
        if (p->b[0] == 1) return 0;
        if (offs == -1) return p->b[4];
        if (offs < p->b[4]) return p->table[offs];
        return 0;
    }
    return 0;
}
