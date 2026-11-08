int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_001084b0(unsigned int addr, int size) {
    int intr = FUN_00113f20();
    *(volatile unsigned int *)0x1000B010 = (addr & 0x0FFFFFFF) | 0x80000000;
    *(volatile int *)0x1000B020 = size >> 4;
    *(volatile int *)0x1000B000 = 0x100;
    if (intr) {
        FUN_00113f78();
    }
}
