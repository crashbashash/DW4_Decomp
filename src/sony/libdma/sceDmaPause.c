int DIntr(void);
int EIntr(void);
unsigned int sceDmaPause(volatile unsigned int *chcr) {
    int intr;
    unsigned int enable;
    unsigned int old;

    intr = DIntr();
    enable = *(volatile unsigned int *)0x1000F520;
    if (!(enable & 0x10000)) {
        *(volatile unsigned int *)0x1000F590 = enable | 0x10000;
    }
    *(volatile unsigned int *)0x1000E000;
    old = *chcr;
    *chcr = old & ~0x100;
    *(volatile unsigned int *)0x1000F590 = enable;
    if (intr) {
        EIntr();
    }
    return old;
}
