typedef struct {
    unsigned char data[32];
    int f32[4];
    unsigned char modes[10][4];
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
int scePadSetButtonInfo(int port, int slot, int mode);
int FUN_00118af8(int port, int slot);
extern int DAT_0055d480[32];
extern int DAT_0055d240;
int FUN_0010e2a8(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
extern int DAT_00485108;
int FUN_00118440(int port, int slot, int v);
int FUN_00118530(int port, int slot, int term, int offs) {
    PadFrame *p;
    if (DAT_0055d290[port][slot].open == 0) return 0;
    p = FUN_00118178(port, slot);
    if (p->b[14] != 1) return 0;
    if (p->b[0] < 2) return 0;
    if (term >= p->b[6]) return 0;
    if (term == -1) return p->b[6];
    switch (offs) {
    case 1:
        return p->modes[term][0];
    case 2:
        return p->modes[term][1];
    case 3:
        return p->modes[term][2];
    case 4:
        return p->modes[term][3];
    }
    return 0;
}
