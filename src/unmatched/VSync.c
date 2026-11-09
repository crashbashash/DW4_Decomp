int FUN_00113f20(void);
int FUN_00113f78(void);
void VSync(void) {
    int interrupts = FUN_00113f20();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) FUN_00113f78();
    while ((*(volatile int *)0x1000F000 & 4) == 0) {
    }
    interrupts = FUN_00113f20();
    *(volatile int *)0x1000F000 = 4;
    __asm__ volatile("sync");
    if (interrupts) FUN_00113f78();
}
