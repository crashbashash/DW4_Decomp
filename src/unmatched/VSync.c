int DIntr(void);
int EIntr(void);
void VSync(void) {
    int interrupts = DIntr();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) EIntr();
    while ((*(volatile int *)0x1000F000 & 4) == 0) {
    }
    interrupts = DIntr();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) EIntr();
}
