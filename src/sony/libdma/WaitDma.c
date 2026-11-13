typedef struct {
    unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 2;
    unsigned int b4 : 4;
    unsigned int b8 : 1;
} Flags;
typedef struct {
    Flags f;
    int pad[3];
    unsigned int x10;
    int pad2[3];
    int x20;
    int pad3[3];
    unsigned int x30;
} Obj;
extern char DAT_004d1e70[];
int scePrintf(const char *fmt, ...);
void sceDmaPause(Obj *o);
void WaitDma(Obj *o) {
    int n = 0x1000000;
    while (*(volatile unsigned int *)o & 0x100) {
        if (--n < 0) {
            scePrintf(DAT_004d1e70);
            sceDmaPause(o);
        }
    }
}
