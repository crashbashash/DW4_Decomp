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

void _ipuFlushBits(char *d, int n) {
    unsigned int cmd;

    IPU_WAIT(d);
    cmd = n | 0x40000000;
    *(volatile unsigned int *)0x10002000 = cmd;
    *(int *)(d + 2096) = DAT_00481cd8[cmd >> 28];
    *(int *)(d + 2128) = FUN_00106660(d);
    *(int *)(d + 2132) = 32;
}
