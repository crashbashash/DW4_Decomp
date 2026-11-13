typedef unsigned int u_int;
int EIntr(void)
{
    u_int stat;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    __asm__("ei");
    return stat != 0;
}
