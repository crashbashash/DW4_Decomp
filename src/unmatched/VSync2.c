int FUN_00113f20(void);
int FUN_00113f78(void);
void SetVSyncFlag(int *flag, unsigned long *time);
unsigned long VSync2(void) {
    int interrupts;
    struct {
        volatile int flag;
        volatile unsigned long time;
    } vsync;
    vsync.flag = 0;
    SetVSyncFlag((int *)&vsync.flag, (unsigned long *)&vsync.time);
    interrupts = FUN_00113f20();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) FUN_00113f78();
    while ((*(volatile int *)0x1000F000 & 4) == 0 && vsync.flag == 0) {
    }
    interrupts = FUN_00113f20();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) FUN_00113f78();
    return vsync.time;
}
