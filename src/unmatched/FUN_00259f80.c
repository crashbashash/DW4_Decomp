void FUN_00259f80(int *arg0) {
    int x;
    x = *(volatile int *)(arg0 + 10);
    asm("nop");
    asm("nop");
}
