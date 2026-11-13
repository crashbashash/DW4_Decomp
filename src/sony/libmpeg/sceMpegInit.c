int DIntr(void);
int EIntr(void);
void sceIpuInit(void);

int sceMpegInit(void) {
    int intr = DIntr();
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | 0x10000;
    *(volatile unsigned int *)0x1000B000 &= ~0x100;
    *(volatile unsigned int *)0x1000B400 &= ~0x100;
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~0x10000;
    if (intr) {
        EIntr();
    }
    *(volatile unsigned int *)0x1000B020 = 0;
    *(volatile unsigned int *)0x1000B420 = 0;
    sceIpuInit();
    return 1;
}
