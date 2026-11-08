int FUN_0010c7b0(int c) {
    while (*(volatile int *)0x1000f130 & 0x8000);
    *(volatile char *)0x1000f180 = c;
    return c;
}
