typedef unsigned int u_int;
int FUN_00113f78(void)
{
    u_int stat;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    __asm__ volatile("ei");
    return stat != 0;
}
