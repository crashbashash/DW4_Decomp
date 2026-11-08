int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_0010a870(void);

int FUN_00108cc8(void) {
    int intr = FUN_00113f20();
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | 0x10000;
    *(volatile unsigned int *)0x1000B000 &= ~0x100;
    *(volatile unsigned int *)0x1000B400 &= ~0x100;
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~0x10000;
    if (intr) {
        FUN_00113f78();
    }
    *(volatile unsigned int *)0x1000B020 = 0;
    *(volatile unsigned int *)0x1000B420 = 0;
    FUN_0010a870();
    return 1;
}
