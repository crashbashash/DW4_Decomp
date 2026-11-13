int DIntr(void);
int EIntr(void);
void setD3_CHCR(unsigned int v) {
    int s = DIntr();
    *(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
    *(volatile unsigned int *)0x1000b000 = v;
    *(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
    if (s) EIntr();
}
