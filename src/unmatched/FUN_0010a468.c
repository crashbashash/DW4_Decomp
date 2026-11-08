int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_0010a468(unsigned int v) {
    int s = FUN_00113f20();
    *(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
    *(volatile unsigned int *)0x1000b000 = v;
    *(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
    if (s) FUN_00113f78();
}
