int DIntr(void);
int EIntr(void);
void SetVSyncFlag(int *flag, unsigned long *time);
unsigned long VSync2(void) {
    int interrupts;
    struct {
        volatile int flag;
        volatile unsigned long time;
    } vsync;
    vsync.flag = 0;
    SetVSyncFlag((int *)&vsync.flag, (unsigned long *)&vsync.time);
    interrupts = DIntr();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) EIntr();
    while ((*(volatile int *)0x1000F000 & 4) == 0 && vsync.flag == 0) {
    }
    interrupts = DIntr();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) EIntr();
    return vsync.time;
}
