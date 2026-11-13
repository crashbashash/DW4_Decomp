extern int DAT_00481cd8[];
long long FUN_00106660(char *d);
void FUN_00109280(int sema);

#define IPU_WAIT(d)                                                                     \
    {                                                                                   \
        int n_ = 0;                                                                     \
        while ((*(volatile unsigned int *)0x10002010 & 0x80004000) == 0x80000000 &&     \
               !*(int *)((d) + 4256)) {                                                 \
            if (n_++ > 5000) {                                                          \
                FUN_00109280(*(int *)((d) + 2160));                                     \
                n_ = 0;                                                                 \
            }                                                                           \
        }                                                                               \
    }
int DIntr(void);
int EIntr(void);

int _ipuVdec(char *d, int type) {
    long long r;
    long long top;
    unsigned int bp;
    int cmd;
    int n = 0;

    IPU_WAIT(d);
    cmd = (type << 26) | 0x30000000;
    *(volatile int *)0x10002000 = cmd;
    *(int *)(d + 2096) = DAT_00481cd8[cmd >> 28];
    while ((r = *(volatile long long *)0x10002000) < 0) {
        if (*(int *)(d + 4256)) {
            int intr = DIntr();
            *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | 0x10000;
            *(volatile unsigned int *)0x1000B400 = 0;
            *(volatile unsigned int *)0x1000B000 = 0;
            *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~0x10000;
            if (intr) {
                EIntr();
            }
            *(volatile unsigned int *)0x1000B020 = 0;
            *(volatile unsigned int *)0x1000B420 = 0;
            *(volatile unsigned int *)0x10002010 = 0x40000000;
            return 0;
        }
        if (n++ > 5000) {
            n = 0;
            FUN_00109280(*(int *)(d + 2160));
        }
    }
    bp = *(volatile unsigned int *)0x10002020;
    top = *(long long *)0x10002030;
    *(int *)(d + 2128) = top;
    if (top < 0) {
        *(int *)(d + 2132) = -(bp & 0x1F) & 0x1F;
    } else {
        *(int *)(d + 2132) = 32;
    }
    *(int *)(d + 308) = (int)r == 0;
    return (short)r;
}
